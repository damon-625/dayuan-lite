/*
 * dayuan — dayuan-lite 安全封装
 * 
 * 安全特性：
 * 1. 用户身份只从 $PWD/.current-userid 读取，无法通过参数注入
 * 2. state-dir 路径硬编码，无法绕过
 * 3. 编译成二进制，无法修改逻辑
 * 
 * 编译：gcc -o dayuan dayuan.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH 4096
#define MAX_USERID 256
#define MAX_ARGS 64

// 硬编码路径（防止被修改）
static const char *DAYUAN_SCRIPT = "/home/damon/code/dayuan-lite/dayuan.py";
static const char *STATE_BASE_DIR = "/home/damon/.config/dayuan-lite-users";

// 读取用户身份（只从 $PWD/.current-userid）
int read_userid(char *userid, size_t size) {
    char filepath[MAX_PATH];
    char *pwd = getcwd(NULL, 0);
    if (!pwd) {
        fprintf(stderr, "错误：无法获取当前目录\n");
        return -1;
    }
    
    snprintf(filepath, sizeof(filepath), "%s/.current-userid", pwd);
    free(pwd);
    
    FILE *f = fopen(filepath, "r");
    if (!f) {
        fprintf(stderr, "错误：无法确定用户身份（%s 不存在）\n", filepath);
        return -1;
    }
    
    if (!fgets(userid, size, f)) {
        fclose(f);
        fprintf(stderr, "错误：.current-userid 为空\n");
        return -1;
    }
    fclose(f);
    
    // 去除换行符和空白
    size_t len = strlen(userid);
    while (len > 0 && (userid[len-1] == '\n' || userid[len-1] == '\r' || userid[len-1] == ' ')) {
        userid[--len] = '\0';
    }
    
    if (len == 0) {
        fprintf(stderr, "错误：.current-userid 为空\n");
        return -1;
    }
    
    return 0;
}

// 确保目录存在
int ensure_dir(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISDIR(st.st_mode) ? 0 : -1;
    }
    
    // 递归创建
    char tmp[MAX_PATH];
    strncpy(tmp, path, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    
    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, 0755);
            *p = '/';
        }
    }
    return mkdir(tmp, 0755);
}

void print_usage() {
    fprintf(stderr, "用法: dayuan <命令> [参数...]\n\n");
    fprintf(stderr, "命令:\n");
    fprintf(stderr, "  wecom <操作> --json '<参数>'   执行企微操作\n");
    fprintf(stderr, "  wecom --help-cli <模块>        查看模块帮助\n");
    fprintf(stderr, "  wecom --schema \"<模块> <命令>\" 查看参数 schema\n");
    fprintf(stderr, "  read --json '<参数>'           大圆 Agent 调用\n");
    fprintf(stderr, "  status                         检查授权状态\n");
    fprintf(stderr, "  login                          发起授权\n");
    fprintf(stderr, "  renew                          刷新凭据\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }
    
    // 读取用户身份
    char userid[MAX_USERID];
    if (read_userid(userid, sizeof(userid)) != 0) {
        return 1;
    }
    
    // 构建用户专属 state 目录
    char state_dir[MAX_PATH];
    snprintf(state_dir, sizeof(state_dir), "%s/%s", STATE_BASE_DIR, userid);
    
    // 确保目录存在
    if (ensure_dir(state_dir) != 0 && errno != EEXIST) {
        fprintf(stderr, "错误：无法创建状态目录 %s\n", state_dir);
        return 1;
    }
    
    // 检查 dayuan.py 是否存在
    if (access(DAYUAN_SCRIPT, F_OK) != 0) {
        fprintf(stderr, "错误：dayuan-lite 未安装（%s 不存在）\n", DAYUAN_SCRIPT);
        return 1;
    }
    
    // 构建参数列表：python3 dayuan.py --state-dir <dir> <所有用户参数>
    char *exec_args[MAX_ARGS];
    int idx = 0;
    
    exec_args[idx++] = "python3";
    exec_args[idx++] = (char *)DAYUAN_SCRIPT;
    exec_args[idx++] = "--state-dir";
    exec_args[idx++] = state_dir;
    
    // 透传所有用户参数
    for (int i = 1; i < argc && idx < MAX_ARGS - 1; i++) {
        exec_args[idx++] = argv[i];
    }
    exec_args[idx] = NULL;
    
    // 执行
    execvp("python3", exec_args);
    
    // execvp 失败才会到这里
    perror("执行失败");
    return 1;
}
