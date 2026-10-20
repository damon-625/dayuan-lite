---
name: wecom-dayuan
description: "Use when querying WeChat Work messages, creating/editing documents or spreadsheets, managing todos, scheduling meetings or calendar events, or searching contacts via DaYuan Agent and wecom-cli."
---

# wecom-dayuan

操作企业微信：消息查询、未读整理、联系人搜索、建群发消息、文档表格、待办、会议、日程。

## Overview

两种调用方式：
1. **大圆 A2A**（`dayuan read`）：消息相关操作，9 个 operation
2. **wecom-cli**（`dayuan wecom-cli`）：文档/表格/待办/会议等结构化操作

## 大圆 A2A 操作（9 个 operation）

| operation | 说明 | 必填参数 | 自动 write |
|-----------|------|---------|----------------|
| `ask` | 自然语言问大圆 | query | 可选 |
| `search_messages` | 搜索消息 | chat, query | ❌ |
| `read_chat` | 读取消息 | chat | ❌ |
| `search_files` | 聊天文件搜索 | chat, query | ❌ |
| `list_unread` | 未读整理（按优先级分档） | - | ❌ |
| `search_groups` | 搜群 | query | ❌ |
| `search_contacts` | 搜联系人 | query | ❌ |
| `create_group` | 建群 | group_name, member_ids | ✅ |
| `send_message` | 发消息 | chat, content/file_path | ✅ |

### 示例

```bash
# 自然语言问
./bin/dayuan read --wait 30 --json '{"operation":"ask","query":"谁找我"}'

# 未读整理
./bin/dayuan read --wait 30 --json '{"operation":"list_unread"}'

# 搜联系人
./bin/dayuan read --wait 30 --json '{"operation":"search_contacts","query":"张三"}'

# 搜群
./bin/dayuan read --wait 30 --json '{"operation":"search_groups","query":"技术群"}'

# 读消息
./bin/dayuan read --wait 30 --json '{"operation":"read_chat","chat":"测试群","limit":20}'

# 搜消息
./bin/dayuan read --wait 30 --json '{"operation":"search_messages","chat":"测试群","query":"部署"}'

# 搜文件
./bin/dayuan read --wait 30 --json '{"operation":"search_files","chat":"测试群","query":"周报"}'

# 发消息（自动 write 模式）
./bin/dayuan read --wait 30 --json '{"operation":"send_message","chat":"测试群","content":"hello""}'

# 建群（自动 write 模式）
./bin/dayuan read --wait 30 --json '{"operation":"create_group","group_name":"新项目群","member_ids":["user1","user2"]"}'
```

## wecom-cli 操作

**透传到 wecom-cli，命令格式完全一致：**

```bash
./bin/dayuan wecom-cli <module> <command> --json '<params>'
```

**探索命令（无需 --json，直接透传）：**

```bash
./bin/dayuan wecom-cli --help                    # 查看所有模块
./bin/dayuan wecom-cli todo --help               # 查看 todo 子命令
./bin/dayuan wecom-cli todo create --schema      # 查看 create 参数
./bin/dayuan wecom-cli todo --doc                # 查看 todo 文档
```

### 常用示例

```bash
# 搜通讯录
./bin/dayuan wecom-cli contact users search --json '{"keywords":["damon"]}'

# 搜文档
./bin/dayuan wecom-cli doc search --json '{"keywords":["周报"]}'

# 创建待办
./bin/dayuan wecom-cli todo create --json '{"items":[{"title":"完成评审"}]}'

# 创建会议
./bin/dayuan wecom-cli meeting create --json '{"subject":"周会","begin_time":"2026-10-20 14:00:00","end_time":"2026-10-20 15:00:00"}'
```

## 支持模块

| 模块 | 命令前缀 | 参考文档 |
|------|----------|----------|
| 消息/未读/联系人/建群/发消息 | dayuan read | [dayuan-ask.md](references/dayuan-ask.md) |
| 通讯录（详细） | wecom-cli contact | [wecom-contact.md](references/wecom-contact.md) |
| 文档 | wecom-cli doc | [wecom-doc.md](references/wecom-doc.md) |
| 表格 | wecom-cli sheet | [wecom-sheet.md](references/wecom-sheet.md) |
| 智能文档 | wecom-cli smartpage | [wecom-smartpage.md](references/wecom-smartpage.md) |
| 智能表格 | wecom-cli smartsheet | [wecom-smartsheet.md](references/wecom-smartsheet.md) |
| 待办 | wecom-cli todo | [wecom-todo.md](references/wecom-todo.md) |
| 会议 | wecom-cli meeting | [wecom-meeting.md](references/wecom-meeting.md) |
| 日程 | wecom-cli calendar | [wecom-calendar.md](references/wecom-calendar.md) |

## Common Mistakes

| 问题 | 解决 |
|------|------|
| `keywords` 传字符串 | 必须是数组：`["关键词"]` |
| `userids` 传对象数组 | 必须是字符串数组：`["userid1"]` |
| `sheet ranges get` 缺 `sheet_id` | 先用 `sheet get` 获取子表 ID |
| `smartpage pages append` 传 content | 必须用 `file_path` 传文件路径 |
