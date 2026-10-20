# 企微智能页面（SmartPage）

使用 wecom-cli 创建、编辑智能页面（类 Notion）。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli smartpage --help
wecom-cli smartpage pages --help

# 查看某个命令的详细参数 schema
wecom-cli smartpage create --schema
wecom-cli smartpage pages get --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `smartpage create` | 创建智能页面 |
| `smartpage import` | 从 Markdown 导入创建页面 |
| `smartpage pages get` | 获取页面内容 |
| `smartpage pages append` | 追加内容 |
| `smartpage pages overwrite` | 覆盖内容 |
| `smartpage pages update` | 修改页面属性 |
| `smartpage blocks delete` | 删除块 |
| `smartpage images upload` | 上传图片 |
| `smartpage files upload` | 上传文件 |

---

## smartpage create - 创建智能页面

创建空白智能页面。

```bash
wecom-cli smartpage create --doc-name <页面名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--doc-name` | **必填** | string | 页面名称 |
| `--space-id` | 选填 | string | 知识空间 ID（不传则创建到个人空间） |

### 示例

```bash
wecom-cli smartpage create --doc-name "项目看板"
```

---

## smartpage import - 从 Markdown 导入创建页面

从 Markdown 文件导入创建智能页面。

```bash
wecom-cli smartpage import --input <文件路径> --doc-name <页面名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--input` | **必填** | string | Markdown 文件路径 |
| `--doc-name` | **必填** | string | 页面名称 |
| `--space-id` | 选填 | string | 知识空间 ID |

### 示例

```bash
wecom-cli smartpage import --input ./README.md --doc-name "项目文档"
```

---

## smartpage pages get - 获取页面内容

获取智能页面内容（Block 结构）。

```bash
wecom-cli smartpage pages get --docid <文档ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |

### 示例

```bash
wecom-cli smartpage pages get --docid "sp_123"
```

---

## smartpage pages append - 追加内容

向页面末尾追加内容（Markdown）。

```bash
wecom-cli smartpage pages append --docid <文档ID> --content <内容>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--content` | **必填** | string | Markdown 内容 |

### 示例

```bash
wecom-cli smartpage pages append --docid "sp_123" --content "## 新章节\n这是新内容"
```

---

## smartpage pages overwrite - 覆盖内容

覆盖页面全部内容（Markdown）。

```bash
wecom-cli smartpage pages overwrite --docid <文档ID> --content <内容>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--content` | **必填** | string | 新的 Markdown 内容 |

### 示例

```bash
wecom-cli smartpage pages overwrite --docid "sp_123" --content "# 标题\n全新内容"
```

---

## smartpage pages update - 修改页面属性

修改页面属性（如名称、图标等）。

```bash
wecom-cli smartpage pages update --docid <文档ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--doc-name` | 选填 | string | 新名称 |
| `--icon` | 选填 | json | 图标配置 |
| `--cover` | 选填 | json | 封面配置 |

### 示例

```bash
wecom-cli smartpage pages update --docid "sp_123" --doc-name "新页面名称"
```

---

## smartpage blocks delete - 删除块

删除页面中的指定块。

```bash
wecom-cli smartpage blocks delete --docid <文档ID> --block-ids <块ID列表>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--block-ids` | **必填** | string[] | 块 ID 列表 |

### 示例

```bash
wecom-cli smartpage blocks delete --docid "sp_123" --block-ids "blk_1" "blk_2"
```

---

## smartpage images upload - 上传图片

上传图片到智能页面，返回图片 URL 供内容引用。

```bash
wecom-cli smartpage images upload --docid <文档ID> --input <文件路径>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--input` | **必填** | string | 图片文件路径 |

### 示例

```bash
wecom-cli smartpage images upload --docid "sp_123" --input ./screenshot.png
```

---

## smartpage files upload - 上传文件

上传文件到智能页面，返回文件 URL。

```bash
wecom-cli smartpage files upload --docid <文档ID> --input <文件路径>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--input` | **必填** | string | 文件路径 |

### 示例

```bash
wecom-cli smartpage files upload --docid "sp_123" --input ./report.pdf
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
