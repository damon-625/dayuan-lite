# 企微通讯录

使用 wecom-cli 搜索通讯录。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli contact --help
wecom-cli contact users --help

# 查看某个命令的详细参数 schema
wecom-cli contact users search --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `contact users search` | 搜索用户 |

---

## contact users search - 搜索用户

按关键词搜索通讯录用户。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `keywords` | **必填** | string[] | 搜索关键词列表，1~10 个 |
| `search_mode` | 选填 | string | 查找模式：`list`=全量列表模式，不传=默认模式 |

### 示例

```bash
# 搜索用户（单关键词）
dayuan-auth exec wecom contact-search --json '{
  "keywords": ["张三"]
}'

# 搜索用户（多关键词）
dayuan-auth exec wecom contact-search --json '{
  "keywords": ["张三", "李四"],
  "search_mode": "list"
}'
```

### 返回字段

| 字段 | 类型 | 说明 |
|------|------|------|
| `users` | array | 用户列表 |
| `users[].userid` | string | 用户 ID（企微内部 ID） |
| `users[].name` | string | 用户姓名 |
| `users[].avatar` | string | 头像 URL |

---

## 通用选项

所有 wecom-cli 命令都支持：

| 选项 | 说明 |
|------|------|
| `--help` | 查看命令帮助 |
| `--schema` | 查看完整参数 schema（最准确）|
| `--dry-run` | 仅本地校验请求，不实际发送 |
| `--json <JSON>` | 请求体原始 JSON 字符串 |
