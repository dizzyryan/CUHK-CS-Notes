int can_exit(char maze[11][11], int x, int y) {
    if (x == 9 && y == 9) {
        return 1;
    }
    maze[y][x] = '@';
    if (maze[y-1][x] == ' ' && can_exit(maze, x, y-1)) {
        return 1;
    }
    if (maze[y+1][x] == ' ' && can_exit(maze, x, y+1)) {
        return 1;
    }
    if (maze[y][x-1] == ' ' && can_exit(maze, x-1, y)) {
        return 1;
    }
    if (maze[y][x+1] == ' ' && can_exit(maze, x+1, y)) {
        return 1;
    }
    return 0;
}
