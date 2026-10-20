# 大圆消息查询

通过大圆 Agent 查询企业微信消息、整理未读、搜索聊天记录。

## 自然语言对话（推荐）

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"<唯一ID>","operation":"ask","query":"<问题>"}'
```

### 参数

| 参数 | 必填 | 说明 |
|------|------|------|
| `request_id` | ✅ | 唯一标识（8-80字符） |
| `operation` | ✅ | 固定 `ask` |
| `query` | ✅ | 问题（最长 500 字符） |

### 示例

```bash
# 整理未读
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"ask-001","operation":"ask","query":"帮我整理一下未读消息"}'

# 总结群聊
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"ask-002","operation":"ask","query":"总结一下今天 3P 产品群讨论了什么"}'

# 发消息（自动写模式）
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"ask-003","operation":"send_message","chat":"张三","content":"收到，马上处理"}'
```

---

## 结构化查询

### 搜索群聊

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"sg-001","operation":"search_groups","query":"开发","limit":10}'
```

| 参数 | 必填 | 说明 |
|------|------|------|
| `operation` | ✅ | 固定 `search_groups` |
| `query` | ✅ | 群名关键词 |
| `limit` | ❌ | 返回数量，默认 10 |

### 读取群消息

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"rc-001","operation":"read_chat","chat":"3P 产品 & 开发","since":"2026-10-17T00:00:00+08:00","until":"2026-10-17T23:59:59+08:00","limit":30}'
```

| 参数 | 必填 | 说明 |
|------|------|------|
| `operation` | ✅ | 固定 `read_chat` |
| `chat` | ✅ | 群名（精确匹配） |
| `since` | ❌ | 开始时间（**必须带时区**，如 `+08:00`） |
| `until` | ❌ | 结束时间（**必须带时区**） |
| `limit` | ❌ | 返回消息数，默认 30 |

### 群内搜索

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec chat --wait 120 --json '{"request_id":"sm-001","operation":"search_messages","chat":"3P 产品 & 开发","query":"发布","limit":10}'
```

| 参数 | 必填 | 说明 |
|------|------|------|
| `operation` | ✅ | 固定 `search_messages` |
| `chat` | ✅ | 群名（精确匹配） |
| `query` | ✅ | 搜索关键词 |
| `limit` | ❌ | 返回数量，默认 10 |

---

## 已知限制

1. **不支持多轮对话**：每次请求独立，追问需把上下文写在 query 里
2. **有频次限制**：达上限需等次日重置
3. **返回是摘要**：不保证逐字原文
