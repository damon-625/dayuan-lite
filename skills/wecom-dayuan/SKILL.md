# wecom-dayuan

通过大圆操作企业微信：消息查询、文档表格、待办、会议、日程、通讯录。

## 安装

1. 修改 `src/dayuan-auth.c` 中的路径
2. 编译：`gcc -o bin/dayuan src/dayuan-auth.c`
3. 工作区创建 `.current-userid` 文件，写入用户标识

## 授权

```bash
# 检查状态
./bin/dayuan status

# 首次授权（扫码）
./bin/dayuan login
```

## 使用

### 大圆 Agent（自然语言查消息）

```bash
./bin/dayuan exec read --wait 120 --json '{
  "operation": "ask",
  "query": "帮我看看最近谁找我"
}'
```

详见 [dayuan-ask.md](references/dayuan-ask.md)

### wecom-cli（结构化操作文档/表格/待办/会议）

```bash
./bin/dayuan exec wecom <操作名> --json '<参数>'
```

示例：

```bash
# 搜索通讯录
./bin/dayuan exec wecom contact-search --json '{"keywords":["damon"]}'

# 搜索文档
./bin/dayuan exec wecom doc-search --json '{"keywords":["周报"]}'

# 创建待办
./bin/dayuan exec wecom todo-create --json '{"title":"完成评审"}'

# 创建会议
./bin/dayuan exec wecom meeting-create --json '{"subject":"周会","begin_time":"2026-10-20 14:00:00","end_time":"2026-10-20 15:00:00"}'
```

## 支持的模块

| 模块 | 说明 | 文档 |
|------|------|------|
| 消息 | 自然语言查消息、搜群、读聊天记录 | [dayuan-ask.md](references/dayuan-ask.md) |
| 通讯录 | 搜索联系人 | [wecom-contact.md](references/wecom-contact.md) |
| 文档 | 创建/搜索/读写普通文档 | [wecom-doc.md](references/wecom-doc.md) |
| 表格 | 读取普通表格 | [wecom-sheet.md](references/wecom-sheet.md) |
| 智能文档 | 创建/编辑智能文档 | [wecom-smartpage.md](references/wecom-smartpage.md) |
| 智能表格 | 创建/增删改查记录 | [wecom-smartsheet.md](references/wecom-smartsheet.md) |
| 待办 | 创建/完成/删除待办 | [wecom-todo.md](references/wecom-todo.md) |
| 会议 | 创建/取消会议 | [wecom-meeting.md](references/wecom-meeting.md) |
| 日程 | 创建/查询日程 | [wecom-calendar.md](references/wecom-calendar.md) |

## 探索命令

不确定参数时用 `--help` 或 `--schema`：

```bash
# 查看模块子命令
wecom-cli todo --help

# 查看参数 schema
wecom-cli todo create --schema
```
