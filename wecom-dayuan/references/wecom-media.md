# 媒体文件操作

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli media --help

# 查看某个命令的详细参数 schema
wecom-cli media upload --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 可用操作

| 操作 | 类型 | 说明 |
|------|------|------|
| media-upload | 写入 | 上传本地文件获取 media_id |

## media-upload

上传本地文件，获取 `media_id`。

```bash
.kiro/skills/wecom-dayuan/bin/dayuan-auth exec wecom media-upload --json '{
  "file_path": "/tmp/example.pdf"
}'
```

**必填参数**：
- `file_path` - 本地文件路径

**返回**：
```json
{
  "type": "file",
  "media_id": "mcXXXXX",
  "created_at": "2026-10-19 15:51:01"
}
```

**媒体类型**（自动识别）：
- `image` - 图片
- `voice` - 语音
- `video` - 视频
- `file` - 其他文件

## 不可用操作

| 操作 | 错误码 | 原因 |
|------|--------|------|
| media-download | 893006 | 授权问题 |

> `media_id` 可用于其他需要媒体 ID 的操作。
