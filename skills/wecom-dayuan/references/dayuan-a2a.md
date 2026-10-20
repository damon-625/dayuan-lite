# 大圆 A2A 操作参考

通过大圆 Agent 进行企微消息、联系人、群聊等操作。

## 操作列表

| operation | 说明 | 必填参数 |
|-----------|------|----------|
| `ask` | 自然语言问大圆 | `query` |
| `list_unread` | 未读整理（三档分类） | - |
| `search_contacts` | 搜联系人（姓名/拼音/英文名/别名） | `query` |
| `search_groups` | 搜群 | `query` |
| `search_messages` | 群内搜索消息 | `chat`, `query` |
| `search_files` | 群内搜索文件 | `chat`, `query` |
| `read_chat` | 读取群聊消息 | `chat` |
| `send_message` | 发消息（文字/图片/文件） | `chat`, (`content` 或 `file_path`) |
| `create_group` | 创建内部群 | `group_name`, `member_ids` |

## 调用示例

```bash
# 自然语言问
./bin/dayuan chat --wait 120 --json '{"operation":"ask","query":"帮我整理未读"}'

# 未读整理
./bin/dayuan chat --wait 60 --json '{"operation":"list_unread"}'

# 搜联系人
./bin/dayuan chat --wait 30 --json '{"operation":"search_contacts","query":"张三"}'

# 搜群
./bin/dayuan chat --wait 30 --json '{"operation":"search_groups","query":"产品"}'

# 读群消息
./bin/dayuan chat --wait 60 --json '{"operation":"read_chat","chat":"3P 产品 & 开发","limit":30}'

# 群内搜消息
./bin/dayuan chat --wait 30 --json '{"operation":"search_messages","chat":"3P 产品 & 开发","query":"发布"}'

# 发消息
./bin/dayuan chat --wait 30 --json '{"operation":"send_message","chat":"张三","content":"收到"}'

# 创建群
./bin/dayuan chat --wait 30 --json '{"operation":"create_group","group_name":"测试群","member_ids":["user1","user2"]}'
```

## 说明

- `send_message` 和 `create_group` 自动使用 write 模式，无需手动指定
- `chat` 参数支持群名或联系人名（精确匹配）
- `since`/`until` 时间参数必须带时区（如 `+08:00`）
- 返回结果是大圆的摘要，不保证逐字原文

## wecom-cli 直调

如需绕过大圆直接调 wecom-cli，参考 `references/` 下的官方文档：
- `wecom-cli-reference.md` — CLI 通用参考
- `wecom-*.md` — 各品类 skill 文档
