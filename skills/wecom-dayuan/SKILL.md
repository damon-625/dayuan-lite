---
name: wecom-dayuan
description: "企微消息查询、智能文档/表格创建编辑、待办管理、会议日程管理、通讯录搜索等操作。触发词：企微消息, 微信消息, 聊天记录, 查群, 谁找我, 未读消息, 最近消息, 群聊搜索, 看看群里, 群里说了什么, wecom, 大圆, 智能文档, 智能表格, 待办, 会议, 日程, 通讯录, 找人"
---

# 企微消息与文档操作

通过大圆 Agent 和 wecom-cli 操作企业微信。**共 79 个操作（只读 24 + 写入 55）**。

---

## 快速使用

### 命令前缀

```bash
.kiro/skills/wecom-dayuan/bin/dayuan <命令> [参数]
```

### 检查授权

```bash
.kiro/skills/wecom-dayuan/bin/dayuan status
```

**正常**：`configured: true`；**需授权**：执行 `login` 扫码

---

## 两种操作方式

### 方式一：大圆 Agent（自然语言，推荐用于消息查询）

```bash
# 自然语言对话
.kiro/skills/wecom-dayuan/bin/dayuan exec read --wait 120 --json '{
  "request_id": "<唯一ID>",
  "operation": "ask",
  "query": "帮我整理一下未读消息"
}'

# 启用写操作（发消息、建群等）
.kiro/skills/wecom-dayuan/bin/dayuan exec read --wait 120 --json '{
  "request_id": "<唯一ID>",
  "operation": "ask",
  "mode": "write",
  "query": "帮我给 xxx 发一条消息"
}'
```

**大圆操作**：`ask`、`search_groups`、`read_chat`、`search_messages`

详见 [dayuan-ask.md](references/dayuan-ask.md)

### 方式二：wecom-cli（结构化调用，用于文档/表格/待办/会议等）

```bash
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom <操作名> --json '<参数JSON>'
```

**常用示例**：

```bash
# 搜索通讯录
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom contact-search --json '{"keywords":["damon"]}'

# 搜索文档
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom doc-search --json '{"keywords":["会议纪要"]}'

# 创建智能文档
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom smartpage-create --json '{"name":"文档标题"}'

# 创建会议
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom meeting-create --json '{"subject":"会议标题","begin_time":"2026-10-20 14:00:00","end_time":"2026-10-20 15:00:00"}'

# 创建日程
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom calendar-create --json '{"subject":"日程标题","begin_time":"2026-10-20 09:00:00","end_time":"2026-10-20 10:00:00"}'

# 创建待办
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom todo-create --json '{"title":"待办事项"}'

# 读取表格
.kiro/skills/wecom-dayuan/bin/dayuan exec wecom sheet-read --json '{"docid":"<docid>","sheet_id":"<sheet_id>","range":"A1:G20"}'
```

---

## 能力概览

| 类别 | 只读操作 | 写操作 | 详细文档 |
|------|----------|--------|----------|
| **消息查询** | ask, search_groups, read_chat, search_messages | - | [dayuan-ask.md](references/dayuan-ask.md) |
| **通讯录** | contact-search | - | [wecom-contact.md](references/wecom-contact.md) |
| **普通文档** | doc-search, doc-read | doc-create, doc-import, doc-rename, doc-rules-update, **doc-contents-append**, **doc-contents-overwrite**, doc-members-update | [wecom-doc.md](references/wecom-doc.md) |
| **智能文档** | smartpage-get, smartpage-databases-get | smartpage-create, smartpage-blocks-update, smartpage-pages-append/overwrite, **smartpage-pages-update**, **smartpage-files-upload**, **smartpage-images-upload** | [wecom-smartpage.md](references/wecom-smartpage.md) |
| **智能表格** | smartsheet-get, smartsheet-sheets-list, smartsheet-records-list, smartsheet-fields-list, smartsheet-views-list, **smartsheet-charts-list** | smartsheet-create, smartsheet-records-add/update/delete/query, smartsheet-fields-add/update/delete, smartsheet-views-add/update/delete, **smartsheet-sheets-add/delete/update**, **smartsheet-charts-add/update/delete**, **smartsheet-files-upload**, **smartsheet-images-upload** | [wecom-smartsheet.md](references/wecom-smartsheet.md) |
| **普通表格** | sheet-get, sheet-read | sheet-create, sheet-import, sheet-subsheets-add/delete/copy/move, **sheet-contents-update**, **sheet-rows-append** | [wecom-sheet.md](references/wecom-sheet.md) |
| **待办** | todo-list, todo-get | todo-create, todo-update, todo-finish, todo-delete | [wecom-todo.md](references/wecom-todo.md) |
| **会议** | meeting-list, meeting-get, meeting-search, **meeting-original-get**, **meeting-rooms-search** | meeting-create, meeting-update, meeting-cancel | [wecom-meeting.md](references/wecom-meeting.md) |
| **日程** | calendar-list, calendar-get, **calendar-search**, **calendar-free-list** | calendar-create, calendar-update, calendar-delete | [wecom-calendar.md](references/wecom-calendar.md) |

---

## 授权管理

| 命令 | 说明 |
|------|------|
| `status` | 检查授权状态 |
| `login` | 发起授权（扫码） |
| `finish` | 完成授权 |
| `renew` | 刷新凭据 |

---

## 重要参数格式

| 操作 | 必需参数 | 说明 |
|------|---------|------|
| contact-search | `keywords` | **字符串数组** `["关键词1", "关键词2"]`，1~10 个 |
| doc-search | `keywords` | **字符串数组**，必填 |
| doc-rename | `docid`, `new_name` | `new_name` 不是 `doc-name` |
| meeting-create | `subject`, `begin_time`, `end_time` | 时间格式 `YYYY-MM-DD HH:MM:SS` |
| calendar-create | `subject`, `begin_time`, `end_time` | 同上 |
| calendar-free-list | `userids`, `begin_time`, `end_time` | `userids` 是**字符串数组** `["userid1", "userid2"]` |
| smartsheet-records-* | `docid`, `sheet_id` | sheet_id 先用 `smartsheet-sheets-list` 获取 |
| smartpage-pages-append | `docid`, `page_id`, `file_path` | **必须用文件路径**，先把内容写入文件再传 `file_path` |
| smartpage-blocks-update | `docid`, `page_id`, `method`, `mdx` | page_id 从 `smartpage-get` 获取 |
| sheet-read | `docid`, `sheet_id` | sheet_id 先用 `sheet-get` 获取，range 可选 |

---

## 已知限制

1. **大圆不支持多轮对话**：每次请求独立，追问需把上下文写在 query 里
2. **大圆有频次限制**：达上限需等次日重置
3. **大圆返回是摘要**：不保证逐字原文
4. **普通表格只读不写**：`sheet-write`、`sheet-append` 不可用，智能表格可写
5. **微盘已移除**：企微接口权限限制，整个模块不可用
6. **邮件未开通**：`mail-*` 操作返回 680212
7. **doc-search 只能搜 doc 类型**：bridge 限制 `doc_types` 固定为 `["doc"]`，无法搜索 sheet/smartsheet/smartpage

---

## 不可用操作（企微接口限制）

| 操作 | 错误码 | 原因 |
|------|--------|------|
| chat 全部 | - | CLI 不支持 |
| message 全部 | 853006 | 消息模块企业未开通 |
| disk 全部 | 640027/640032 | 微盘模块已移除 |
| media 全部 | - | 媒体模块已移除 |
| sheet-subsheets-rename | 640027 | 权限不足 |
| smartpage-import | 893006 | 不支持 |
| smartsheet-import | CLI_FAILED | 不支持 |
| smartsheet-charts-* | 640027 | 图表功能受限 |
| doc-members-update | 640027 | 协作成员管理受限 |

> **注**：加粗操作是新增接口，部分因企微权限限制暂不可用。sheet-contents-update、sheet-rows-append、doc-contents-append/overwrite、smartsheet-sheets-add、calendar-search、calendar-free-list、meeting-rooms-search 等已验证可用。
