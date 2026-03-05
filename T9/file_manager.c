#include <ncurses.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FILES 1000
#define MAX_PATH 1024

typedef struct {
    char name[256];
    int is_dir;
    off_t size;
} FileEntry;

typedef struct {
    char path[MAX_PATH];
    FileEntry files[MAX_FILES];
    int file_count;
    int selected;
    int scroll_offset;
    int active;
} Panel;

Panel left_panel, right_panel;
Panel *current_panel;
int height, width;

void init_panel(Panel *panel, const char *path) {
    strncpy(panel->path, path, MAX_PATH - 1);
    panel->path[MAX_PATH - 1] = '\0';
    panel->file_count = 0;
    panel->selected = 0;
    panel->scroll_offset = 0;
    panel->active = 0;
}

void load_directory(Panel *panel) {
    DIR *dir = opendir(panel->path);
    if (!dir) return;
    
    panel->file_count = 0;
    struct dirent *entry;
    
    strcpy(panel->files[0].name, "..");
    panel->files[0].is_dir = 1;
    panel->files[0].size = 0;
    panel->file_count = 1;
    
    while ((entry = readdir(dir)) != NULL && panel->file_count < MAX_FILES) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        strcpy(panel->files[panel->file_count].name, entry->d_name);
        
        char full_path[MAX_PATH];
        snprintf(full_path, MAX_PATH, "%s/%s", panel->path, entry->d_name);
        
        struct stat st;
        if (stat(full_path, &st) == 0) {
            panel->files[panel->file_count].is_dir = S_ISDIR(st.st_mode);
            panel->files[panel->file_count].size = st.st_size;
        }
        
        panel->file_count++;
    }
    
    closedir(dir);
    
    for (int i = 1; i < panel->file_count; i++) {
        for (int j = i + 1; j < panel->file_count; j++) {
            if (panel->files[i].is_dir < panel->files[j].is_dir ||
                (panel->files[i].is_dir == panel->files[j].is_dir && 
                 strcasecmp(panel->files[i].name, panel->files[j].name) > 0)) {
                FileEntry temp = panel->files[i];
                panel->files[i] = panel->files[j];
                panel->files[j] = temp;
            }
        }
    }
}

void draw_panel(Panel *panel, int x, int w) {
    int panel_height = height - 4;
    
    attron(COLOR_PAIR(panel->active ? 3 : 2));
    mvhline(1, x, ACS_HLINE, w);
    mvhline(height - 2, x, ACS_HLINE, w);
    mvvline(2, x, ACS_VLINE, panel_height);
    mvvline(2, x + w - 1, ACS_VLINE, panel_height);
    mvaddch(1, x, ACS_ULCORNER);
    mvaddch(1, x + w - 1, ACS_URCORNER);
    mvaddch(height - 2, x, ACS_LLCORNER);
    mvaddch(height - 2, x + w - 1, ACS_LRCORNER);
    attroff(COLOR_PAIR(panel->active ? 3 : 2));
    
    attron(COLOR_PAIR(4) | A_BOLD);
    char title[MAX_PATH];
    snprintf(title, w - 2, " %s ", panel->path);
    mvprintw(1, x + 1, "%-*s", w - 2, title);
    attroff(COLOR_PAIR(4) | A_BOLD);
    
    int visible_rows = panel_height - 1;
    
    if (panel->selected < panel->scroll_offset)
        panel->scroll_offset = panel->selected;
    if (panel->selected >= panel->scroll_offset + visible_rows)
        panel->scroll_offset = panel->selected - visible_rows + 1;
    
    for (int i = 0; i < visible_rows && (i + panel->scroll_offset) < panel->file_count; i++) {
        int idx = i + panel->scroll_offset;
        int y = 2 + i;
        FileEntry *file = &panel->files[idx];
        
        if (idx == panel->selected) {
            attron(COLOR_PAIR(1));
            mvprintw(y, x + 1, "%-*s", w - 2, "");
        }
        
        char display[256];
        if (file->is_dir) {
            snprintf(display, sizeof(display), "/%-*s", w - 4, file->name);
            attron(COLOR_PAIR(5) | A_BOLD);
        } else {
            snprintf(display, sizeof(display), " %-*s", w - 4, file->name);
            attron(COLOR_PAIR(6));
        }
        
        mvprintw(y, x + 2, "%s", display);
        
        if (!file->is_dir && idx != 0) {
            attron(COLOR_PAIR(6));
            char size_str[32];
            if (file->size < 1024)
                snprintf(size_str, sizeof(size_str), "%ldB", file->size);
            else if (file->size < 1024 * 1024)
                snprintf(size_str, sizeof(size_str), "%ldK", file->size / 1024);
            else
                snprintf(size_str, sizeof(size_str), "%ldM", file->size / (1024 * 1024));
            
            mvprintw(y, x + w - 10, "%8s", size_str);
        }
        
        attroff(COLOR_PAIR(1) | COLOR_PAIR(5) | COLOR_PAIR(6) | A_BOLD);
    }
    
    attron(COLOR_PAIR(2));
    for (int i = panel->file_count - panel->scroll_offset; i < visible_rows; i++) {
        mvprintw(2 + i, x + 1, "%-*s", w - 2, "");
    }
    attroff(COLOR_PAIR(2));
}

void draw_interface() {
    clear();
    
    int panel_width = (width - 1) / 2;
    
    draw_panel(&left_panel, 0, panel_width);
    draw_panel(&right_panel, panel_width + 1, panel_width);
    
    attron(COLOR_PAIR(2));
    mvvline(1, panel_width, ACS_VLINE, height - 3);
    mvaddch(1, panel_width, ACS_TTEE);
    mvaddch(height - 2, panel_width, ACS_BTEE);
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(4) | A_REVERSE);
    mvprintw(height - 1, 0, "%-*s", width, 
             " Tab:Change panel  k/j or Up/Dn:File Navigation  Enter/Rgt:Enter directory  Lft:Exit directory  Home/g:Top of list  End/G:End of list  q:Quit ");
    attroff(COLOR_PAIR(4) | A_REVERSE);
    
    refresh();
}

void enter_directory(Panel *panel) {
    if (panel->file_count == 0) return;
    
    FileEntry *selected = &panel->files[panel->selected];
    if (!selected->is_dir) return;
    
    char new_path[MAX_PATH];
    if (strcmp(selected->name, "..") == 0) {
        char *last_slash = strrchr(panel->path, '/');
        if (last_slash && last_slash != panel->path) {
            strncpy(new_path, panel->path, last_slash - panel->path);
            new_path[last_slash - panel->path] = '\0';
        } else {
            strcpy(new_path, "/");
        }
    } else {
        snprintf(new_path, MAX_PATH, "%s/%s", panel->path, selected->name);
    }
    
    if (access(new_path, R_OK | X_OK) == 0) {
        strncpy(panel->path, new_path, MAX_PATH - 1);
        panel->selected = 0;
        panel->scroll_offset = 0;
        load_directory(panel);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    
    getmaxyx(stdscr, height, width);
    
    char cwd[MAX_PATH];
    getcwd(cwd, MAX_PATH);
    
    init_panel(&left_panel, cwd);
    init_panel(&right_panel, "/");
    left_panel.active = 1;
    current_panel = &left_panel;
    
    load_directory(&left_panel);
    load_directory(&right_panel);

    int running = 1;
    
    while (running) {
        draw_interface();
        
        int ch = getch();
        
        switch (ch) {
            case '\t':
                left_panel.active = !left_panel.active;
                right_panel.active = !right_panel.active;
                current_panel = left_panel.active ? &left_panel : &right_panel;
                break;
                
            case KEY_UP:
            case 'k':
                if (current_panel->selected > 0)
                    current_panel->selected--;
                break;
                
            case KEY_DOWN:
            case 'j':
                if (current_panel->selected < current_panel->file_count - 1)
                    current_panel->selected++;
                break;
                
            case KEY_HOME:
            case 'g':
                current_panel->selected = 0;
                break;
                
            case KEY_END:
            case 'G':
                current_panel->selected = current_panel->file_count - 1;
                break;
                
            case KEY_PPAGE:
                current_panel->selected -= (height - 5);
                if (current_panel->selected < 0) current_panel->selected = 0;
                break;
                
            case KEY_NPAGE:
                current_panel->selected += (height - 5);
                if (current_panel->selected >= current_panel->file_count)
                    current_panel->selected = current_panel->file_count - 1;
                break;
                
            case '\n':
            case KEY_RIGHT:
                enter_directory(current_panel);
                break;
                
            case KEY_LEFT:
                current_panel->selected = 0;
                enter_directory(current_panel);
                break;
                
            case KEY_F(10):
            case 'q':
                running = 0;
                break;
                
            case KEY_RESIZE:
                getmaxyx(stdscr, height, width);
                break;
        }
    }
    
    endwin();
    return 0;
}