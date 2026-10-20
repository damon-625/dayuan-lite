# 企微智能文档

使用 wecom-cli 创建、编辑、管理智能文档。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli doc --help

# 查看某个命令的详细参数 schema
wecom-cli doc create --schema
wecom-cli doc contents get --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `doc create` | 创建智能文档 |
| `doc import` | 从 Markdown 导入创建文档 |
| `doc search` | 搜索文档 |
| `doc contents get` | 获取文档内容 |
| `doc contents append` | 追加内容 |
| `doc contents overwrite` | 覆盖内容 |
| `doc names update` | 修改文档名称 |
| `doc members update` | 修改文档权限 |
| `doc rules update` | 修改安全设置 |

---

## doc create - 创建智能文档

创建空白智能文档。

```bash
wecom-cli doc create --doc-name <文档名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--doc-name` | **必填** | string | 文档名称 |
| `--space-id` | 选填 | string | 知识空间 ID（不传则创建到个人空间） |

### 示例

```bash
wecom-cli doc create --doc-name "项目文档"
```

---

## doc import - 从 Markdown 导入创建文档

从 Markdown 文件导入创建智能文档。

```bash
wecom-cli doc import --input <文件路径> --doc-name <文档名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--input` | **必填** | string | Markdown 文件路径 |
| `--doc-name` | **必填** | string | 文档名称 |
| `--space-id` | 选填 | string | 知识空间 ID |

### 示例

```bash
wecom-cli doc import --input ./README.md --doc-name "项目说明"
```

---

## doc search - 搜索文档

按关键词搜索文档。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `keywords` | **必填** | string[] | 搜索关键词数组，1~20 个 |
| `search_scope` | 选填 | string | 搜索范围：`title`/`title_content`/`content`，默认 `title_content` |
| `doc_types` | 选填 | string[] | 文档类型过滤：`doc`/`sheet`/`smartsheet`/`ppt`/`smartpage` 等 |
| `limit` | 选填 | int | 返回数量上限，默认 10，最大 100 |
| `cursor` | 选填 | string | 分页游标 |

### 示例

```bash
# 搜索文档
dayuan-auth exec wecom doc-search --json '{
  "keywords": ["需求", "设计"]
}'

# 只搜索智能表格
dayuan-auth exec wecom doc-search --json '{
  "keywords": ["销售"],
  "doc_types": ["smartsheet"],
  "limit": 5
}'
```

---

## doc contents get - 获取文档内容

获取指定文档的内容。

```bash
wecom-cli doc contents get --docid <文档ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |

### 示例

```bash
wecom-cli doc contents get --docid "doc_123"
```

---

## doc contents append - 追加内容

向文档末尾追加内容（Markdown）。

```bash
wecom-cli doc contents append --docid <文档ID> --content <内容>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--content` | **必填** | string | Markdown 内容 |

### 示例

```bash
wecom-cli doc contents append --docid "doc_123" --content "## 新章节\n这是新内容"
```

---

## doc contents overwrite - 覆盖内容

覆盖文档全部内容（Markdown）。

```bash
wecom-cli doc contents overwrite --docid <文档ID> --content <内容>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--content` | **必填** | string | 新的 Markdown 内容 |

### 示例

```bash
wecom-cli doc contents overwrite --docid "doc_123" --content "# 标题\n全新内容"
```

---

## doc names update - 修改文档名称

修改文档名称。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `docid` | **必填** | string | 文档 ID 或 URL |
| `new_name` | **必填** | string | 新名称，1~255 字符 |

### 示例

```bash
dayuan-auth exec wecom doc-rename --json '{
  "docid": "w3_xxx",
  "new_name": "新文档名称"
}'
```

---

## doc members update - 修改文档权限

修改文档的成员权限。

```bash
wecom-cli doc members update --docid <文档ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--add` | 选填 | json_array | 新增权限，格式：`[{"userid": "xxx", "right": 3}, ...]` |
| `--remove` | 选填 | json_array | 移除权限，格式：`[{"userid": "xxx"}, ...]` |

**权限值（right）说明**：
- `1`: 只读
- `2`: 可编辑
- `3`: 管理员

### 示例

```bash
# 添加编辑权限
wecom-cli doc members update --docid "doc_123" --add '[{"userid": "user1", "right": 2}]'

# 移除权限
wecom-cli doc members update --docid "doc_123" --remove '[{"userid": "user2"}]'
```

---

## doc rules update - 修改安全设置

修改文档的安全规则。

```bash
wecom-cli doc rules update --docid <文档ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--enable-share-url` | 选填 | flag | 是否允许分享链接 |
| `--enable-readonly-copy` | 选填 | flag | 只读者是否可复制 |
| `--share-scope` | 选填 | int | 分享范围（枚举） |
| `--show-history` | 选填 | flag | 是否展示历史记录 |
| `--show-visitor` | 选填 | flag | 是否展示访客列表 |
| `--enable-comment` | 选填 | flag | 是否允许评论 |
| `--enable-default-external-access` | 选填 | flag | 是否默认允许外部访问 |

### 示例

```bash
# 开启分享链接和评论
wecom-cli doc rules update --docid "doc_123" --enable-share-url --enable-comment
```

---

## 通用选项

所有命令都支持以下选项：

| 选项 | 说明 |
|------|------|
| `--dry-run` | 仅本地校验请求，不实际发送 |
| `--json <JSON>` | 请求体原始 JSON 字符串 |
| `--set <path=val>` | 深层路径覆盖，可重复使用 |
| `-o, --output <file>` | 将响应体写入文件 |
