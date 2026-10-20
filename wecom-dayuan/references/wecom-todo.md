# 企微待办管理

使用 wecom-cli 管理待办事项。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli todo --help

# 查看某个命令的详细参数 schema
wecom-cli todo create --schema
wecom-cli todo list --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `todo list` | 查询待办列表 |
| `todo get` | 批量获取待办详情 |
| `todo create` | 批量创建待办 |
| `todo update` | 批量更新待办 |
| `todo finish` | 批量完成待办 |
| `todo delete` | 批量删除待办 |

---

## todo list - 查询待办列表

读取机器人为创建人、对话人为参与人的待办列表（按 update_time 降序）。

### 参数

| 参数 | 类型 | 说明 |
|------|------|------|
| `status_filter` | string[] | 状态过滤，不传默认返回 `proceed`。枚举：`proceed`（进行中）、`finished`（已完成）|
| `keywords` | string[] | 关键词过滤，单元素内空格为 AND，多元素之间为 OR |
| `create_begin_time` | string | 创建开始时间，格式：`YYYY-MM-DD HH:mm:ss` |
| `create_end_time` | string | 创建结束时间 |
| `deadline_begin_time` | string | 截止开始时间 |
| `deadline_end_time` | string | 截止结束时间 |
| `limit` | int | 最大返回数量，默认 10，最大 20 |
| `cursor` | string | 分页游标 |

### 示例

```bash
dayuan-auth exec wecom todo-list --json '{
  "keywords": ["周报"],
  "limit": 5
}'
```

---

## todo get - 批量获取待办详情

批量读取待办详情，返回标题/描述/参与人/时间等。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `items` | **必填** | array | 待办 ID 列表，最多 20 个 |

### items 元素结构

| 字段 | 必填 | 说明 |
|------|:----:|------|
| `todo_id` | **必填** | 待办 ID |

### 示例

```bash
dayuan-auth exec wecom todo-get --json '{
  "items": [{"todo_id": "abc123"}, {"todo_id": "def456"}]
}'
```

---

## todo create - 批量创建待办

机器人视角批量创建待办。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `items` | **必填** | array | 批量创建待办列表，最多 20 条 |

### items 元素结构

| 字段 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `title` | **必填** | string | 待办标题，最长 4000 字节 |
| `description` | 选填 | string | 待办描述，最长 4000 字节 |
| `follower_ids` | 选填 | string[] | 参与人 userid 列表（最多 50 人）|
| `deadline` | 选填 | object | 截止时间 |
| `remind_at_deadline` | 选填 | bool | 是否在截止时间点提醒 |

### deadline 对象结构

| 字段 | 必填 | 说明 |
|------|:----:|------|
| `type` | **必填** | `date`（日期）或 `datetime`（具体时刻）|
| `value` | **必填** | date=`YYYY-MM-DD`，datetime=`YYYY-MM-DD HH:mm:ss` |

### 示例

```bash
# 只给自己创建待办
dayuan-auth exec wecom todo-create --json '{
  "title": "完成周报"
}'

# 创建带参与人和截止时间的待办
dayuan-auth exec wecom todo-create --json '{
  "title": "完成周报",
  "description": "本周工作总结",
  "follower_ids": ["wo65jOUwAAq0wZl5XiLr22gcQZeodplg"],
  "deadline": {"type": "datetime", "value": "2026-03-15 18:00:00"}
}'
```

> dayuan-auth 支持简化格式（自动转成 items 数组）

---

## todo update - 批量更新待办

机器人视角批量更新待办（标题/描述/参与人/截止时间等）。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `items` | **必填** | array | 批量更新待办列表，最多 20 条 |

### items 元素结构

| 字段 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `todo_id` | **必填** | string | 待办 ID |
| `title` | 选填 | string | 新标题 |
| `description` | 选填 | string | 新描述 |
| `deadline` | 选填 | object | 新截止时间（同 create 的格式）|
| `followers` | 选填 | array | **全量替换**参与人列表，格式：`[{userid: "xxx"}, ...]` |
| `remind_at_deadline` | 选填 | bool | 是否在截止时间点提醒 |

> ⚠️ **注意**：`followers` 是全量替换，已有的参与人会被全部替换，如无需移除应重新传入。

### 示例

```bash
# 更新标题和添加参与人
dayuan-auth exec wecom todo-update --json '{
  "items": [{
    "todo_id": "abc123",
    "title": "更新后的标题",
    "followers": [
      {"userid": "wo65jOUwAAD1qicpBLyDRIbuiuFBkHJA"},
      {"userid": "wo65jOUwAAq0wZl5XiLr22gcQZeodplg"}
    ]
  }]
}'
```

---

## todo finish - 批量完成待办

机器人视角批量完成待办。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `items` | **必填** | array | 批量完成待办列表，最多 20 条 |

### items 元素结构

| 字段 | 必填 | 说明 |
|------|:----:|------|
| `todo_id` | **必填** | 待办 ID |
| `finished_all` | 选填 | `true`=以创建人（机器人）身份整体完成该待办；`false`或不传=只完成调用方用户自己那一份 |

> 不传 `finished_all` 时，返回会包含 `ask_finish_all` 字段询问是否要完成整个待办。

### 示例

```bash
# 只完成自己的份（多人待办时）
dayuan-auth exec wecom todo-finish --json '{
  "items": [{"todo_id": "abc123"}]
}'

# 整体完成待办（包括所有参与人）
dayuan-auth exec wecom todo-finish --json '{
  "items": [{"todo_id": "abc123", "finished_all": true}]
}'
```

---

## todo delete - 批量删除待办

机器人视角批量删除待办。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `items` | **必填** | array | 批量删除待办列表，最多 20 条 |

### items 元素结构

| 字段 | 必填 | 说明 |
|------|:----:|------|
| `todo_id` | **必填** | 待办 ID |

### 示例

```bash
dayuan-auth exec wecom todo-delete --json '{
  "items": [{"todo_id": "abc123"}]
}'
```

---

## 通用选项

所有 wecom-cli 命令都支持：

| 选项 | 说明 |
|------|------|
| `--help` | 查看命令帮助 |
| `--schema` | 查看完整参数 schema（最准确）|
| `--dry-run` | 仅本地校验请求，不实际发送 |
| `--json <JSON>` | 请求体原始 JSON 字符串 |
