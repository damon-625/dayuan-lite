# 微盘操作

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli disk --help
wecom-cli disk files --help

# 查看某个命令的详细参数 schema
wecom-cli disk files list --schema
wecom-cli disk files search --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 可用操作

| 操作 | 类型 | 说明 |
|------|------|------|
| disk-list | 只读 | 列出最近查看的文件 |
| disk-search | 只读 | 搜索微盘文件 |
| disk-get | 只读 | 获取文件详情 |

## disk-list

列出最近查看的文件。

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec wecom disk-list --json '{
  "limit": 10
}'
```

**参数**：
- `limit` - 返回数量（最大100）
- `cursor` - 分页游标

## disk-search

搜索微盘文件。

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec wecom disk-search --json '{
  "keywords": ["季度汇报"],
  "limit": 10
}'
```

**参数**：
- `keywords` - 关键词数组（or 关系）
- `file_types` - 文件类型过滤，可选值：
  - 在线文档：`doc`、`sheet`、`ppt`、`smartsheet`、`smartpage`、`collect`、`mind`、`flow`、`journal`
  - 离线文件：`pdf`、`offline_word`、`offline_excel`、`offline_ppt`、`offline_pdf`、`image`、`videoaudio`、`design`
- `search_type` - 搜索范围：`all`、`file`、`folder`、`space`
- `sort_by` - 排序：`best_match`、`modify_time`、`file_size`
- `sort_order` - 排序方向：`asc`、`desc`
- `limit` - 返回数量（最大100）
- `cursor` - 分页游标

**返回**：
```json
{
  "files": [
    {
      "id": "file_id",
      "file_name": "文件名",
      "type": "file",
      "docid": "a1_XXX",
      "doc_url": "https://doc.weixin.qq.com/...",
      "path": "/空间名/文件夹/文件名"
    }
  ]
}
```

## 不可用操作

| 操作 | 错误码 | 原因 |
|------|--------|------|
| disk-get | 40073 | 接口限制 |
| disk-upload | 640032 | 接口限制 |
| disk-download | 893003 | 接口限制 |
| disk-rename | 893003 | 接口限制 |
| disk-folders-create | -1 | 接口限制 |

> 微盘目前**只支持搜索和列表**，不支持上传/下载/重命名等操作。

## disk-rename

重命名微盘文件。

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec wecom disk-rename --json '{
  "file_id": "fiXXX...",
  "new_name": "新文件名"
}'
```

## disk-get

获取微盘文件/文件夹详情。

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec wecom disk-get --json '{"fileid":"<文件ID>"}'
```

| 参数 | 必填 | 说明 |
|------|------|------|
| `fileid` | ✅ | 文件/文件夹 ID（从 disk-list 或 disk-search 获取） |

返回文件名、大小、修改时间、创建者等信息。
