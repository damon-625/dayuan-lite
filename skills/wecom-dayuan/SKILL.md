---
name: wecom-dayuan
description: "Use when querying WeChat Work messages, creating/editing documents or spreadsheets, managing todos, scheduling meetings or calendar events, or searching contacts via DaYuan Agent and wecom-cli."
---

# wecom-dayuan

操作企业微信：消息查询、文档表格、待办、会议、日程、通讯录。

## Overview

通过大圆 Agent（自然语言）和 wecom-cli（结构化调用）操作企业微信。大圆适合查消息，wecom-cli 适合操作文档/表格/待办/会议。

## When to Use

- 查企微消息、未读、谁找我
- 搜索/创建/编辑文档、表格、智能文档、智能表格
- 创建/完成/删除待办
- 创建/取消会议、查询日程
- 搜索通讯录联系人

## Quick Reference

| 场景 | 命令 |
|------|------|
| 查消息 | `./bin/dayuan read --json '{"operation":"ask","query":"谁找我"}'` |
| 搜通讯录 | `./bin/dayuan wecom-cli contact users search --json '{"keywords":["damon"]}'` |
| 搜文档 | `./bin/dayuan wecom-cli doc search --json '{"keywords":["周报"]}'` |
| 创建待办 | `./bin/dayuan wecom-cli todo create --json '{"items":[{"title":"完成评审"}]}'` |
| 创建会议 | `./bin/dayuan wecom-cli meeting create --json '{"subject":"周会","begin_time":"2026-10-20 14:00:00","end_time":"2026-10-20 15:00:00"}'` |

## Implementation

### 大圆 Agent（自然语言）

```bash
./bin/dayuan read --wait 120 --json '{
  "operation": "ask",
  "query": "帮我看看最近谁找我"
}'
```

详见 [dayuan-ask.md](references/dayuan-ask.md)

### wecom-cli（结构化调用）

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

## 支持模块

| 模块 | 命令前缀 | 参考文档 |
|------|----------|----------|
| 消息查询 | dayuan read | [dayuan-ask.md](references/dayuan-ask.md) |
| 通讯录 | wecom-cli contact | [wecom-contact.md](references/wecom-contact.md) |
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
