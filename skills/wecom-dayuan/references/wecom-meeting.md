# 企微会议管理

使用 wecom-cli 管理会议。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli meeting --help

# 查看某个命令的详细参数 schema
wecom-cli meeting create --schema
wecom-cli meeting rooms search --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `meeting list` | 查询会议列表 |
| `meeting get` | 获取会议详情 |
| `meeting create` | 创建会议 |
| `meeting update` | 更新会议 |
| `meeting cancel` | 取消会议 |
| `meeting search` | 搜索会议 |
| `meeting rooms search` | 查询会议室 |

---

## meeting list - 查询会议列表

按时间范围拉取会议列表。

```bash
wecom-cli meeting list [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--begin-time` | 选填 | string | 过滤范围起始时间，格式：`YYYY-MM-DD HH:mm:ss`。不传默认当前时间 |
| `--end-time` | 选填 | string | 过滤范围截止时间，格式：`YYYY-MM-DD HH:mm:ss`。不传默认当前时间 +30 天 |
| `--limit` | 选填 | int | 每页数量，默认 20，上限 100 |
| `--cursor` | 选填 | string | 分页游标 |

### 示例

```bash
# 查询本周会议
wecom-cli meeting list --begin-time "2026-03-11 00:00:00" --end-time "2026-03-17 23:59:59"
```

---

## meeting get - 获取会议详情

获取会议详情，包含标题、时间、参与人、会议室、智能纪要地址、录制文件地址等。

```bash
wecom-cli meeting get --meeting-ids '<json_array>'
# 或
wecom-cli meeting get --urls <url1> <url2> ...
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--meeting-ids` | 选填* | json_array | 会议 ID 列表，格式：`[{"meeting_id": "xxx"}, ...]`。与 `--urls` 至少传其一 |
| `--urls` | 选填* | string[] | 会议 URL 列表。与 `--meeting-ids` 至少传其一，两者合计上限 10 |

### 示例

```bash
wecom-cli meeting get --meeting-ids '[{"meeting_id": "mtg_123"}]'
```

---

## meeting create - 创建会议

创建会议。

```bash
wecom-cli meeting create --subject <标题> --begin-time <开始时间> --end-time <结束时间> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--subject` | **必填** | string | 会议标题，1~255 字节 |
| `--begin-time` | **必填** | string | 会议开始时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--end-time` | **必填** | string | 会议结束时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--attendees` | 选填 | json_array | 参与人列表，格式：`[{"userid": "xxx"}, ...]` |
| `--location` | 选填 | string | 地点，最长 128 字节 |
| `--description` | 选填 | string | 备注，最长 500 字 |
| `--meeting-room-id` | 选填 | string | 会议室 ID，传入会预定会议室 |
| `--cal-id` | 选填 | string | 所属日历本 ID |
| `--recurrence` | 选填 | json | 周期规则，不传或 `is_repeat=false` 即创建单次会议 |
| `--timezone` | 选填 | json | 时区信息 |
| `--mark-optional-attendees` | 选填 | string[] | 标记可选参与人 |

### 示例

```bash
# 创建简单会议
wecom-cli meeting create \
  --subject "项目启动会" \
  --begin-time "2026-03-15 14:00:00" \
  --end-time "2026-03-15 15:00:00"

# 创建带参与人和会议室的会议
wecom-cli meeting create \
  --subject "周会" \
  --begin-time "2026-03-15 10:00:00" \
  --end-time "2026-03-15 11:00:00" \
  --attendees '[{"userid": "user1"}, {"userid": "user2"}]' \
  --meeting-room-id "room_123" \
  --description "每周例会"
```

---

## meeting update - 更新会议

更新预定会议信息。

```bash
wecom-cli meeting update --meeting-id <会议ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--meeting-id` | **必填** | string | 会议 ID |
| `--subject` | 选填 | string | 新标题 |
| `--begin-time` | 选填 | string | 新开始时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--end-time` | 选填 | string | 新结束时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--location` | 选填 | string | 新地点，传空表示清空 |
| `--description` | 选填 | string | 新备注，传空表示清空 |
| `--meeting-room-id` | 选填 | string | 会议室 ID |
| `--add-attendees` | 选填 | json_array | 新增参与人列表，格式：`[{"userid": "xxx"}, ...]` |
| `--remove-attendees` | 选填 | json_array | 移除参与人列表，格式：`[{"userid": "xxx"}, ...]` |
| `--sub-meeting-id` | 选填 | string | 子会议 ID，周期会议场景下标记要修改的某一场子会议（周期会议必填） |
| `--repeat-edit-type` | 选填 | string | 周期会议修改类型（周期会议必填） |

### 示例

```bash
# 修改会议标题和时间
wecom-cli meeting update \
  --meeting-id "mtg_123" \
  --subject "新标题" \
  --begin-time "2026-03-15 15:00:00" \
  --end-time "2026-03-15 16:00:00"

# 添加和移除参与人
wecom-cli meeting update \
  --meeting-id "mtg_123" \
  --add-attendees '[{"userid": "user3"}]' \
  --remove-attendees '[{"userid": "user1"}]'
```

---

## meeting cancel - 取消会议

取消预定会议，周期会议取消单次需指定子会议 ID。

```bash
wecom-cli meeting cancel --meeting-id <会议ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--meeting-id` | **必填** | string | 会议 ID |
| `--sub-meeting-id` | 选填 | string | 子会议 ID，取消周期会议的单次时需要 |

### 示例

```bash
# 取消单次会议
wecom-cli meeting cancel --meeting-id "mtg_123"

# 取消周期会议的某一场
wecom-cli meeting cancel --meeting-id "mtg_123" --sub-meeting-id "sub_456"
```

---

## meeting search - 搜索会议

按关键词搜索会议。

```bash
wecom-cli meeting search [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--keywords` | 选填 | string[] | 搜索关键词，用于匹配会议主题 |
| `--begin-time` | 选填 | string | 搜索开始时间，格式：`YYYY-MM-DD HH:mm:ss` |
| `--end-time` | 选填 | string | 搜索结束时间，格式：`YYYY-MM-DD HH:mm:ss`。不传默认 `2999-01-01 00:00:00` |
| `--limit` | 选填 | int | 限制返回数量，最大 20，默认 20 |
| `--cursor` | 选填 | string | 分页游标 |
| `--sessionid` | 选填 | string | 会话 sessionid（群聊或单聊），触发客户端召回并与服务端召回结果求交集 |
| `--bot-source` | 选填 | int | 机器人来源 |

### 示例

```bash
# 按关键词搜索
wecom-cli meeting search --keywords "周会"

# 搜索指定时间范围内的会议
wecom-cli meeting search --keywords "评审" --begin-time "2026-03-01 00:00:00" --end-time "2026-03-31 23:59:59"
```

---

## meeting rooms search - 查询会议室

查询会议室。

```bash
wecom-cli meeting rooms search --begin-time <开始时间> --end-time <结束时间> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--begin-time` | **必填** | string | 查询开始时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--end-time` | **必填** | string | 查询结束时间，格式：`YYYY-MM-DD HH:MM:SS` |
| `--building-city` | 选填 | string | 城市名称 |
| `--building-name` | 选填 | string | 大楼名称 |
| `--floor-name` | 选填 | string | 楼层名称 |
| `--room-keyword` | 选填 | string | 会议室名称关键词 |
| `--min-capacity` | 选填 | int | 会议室最小容量 |
| `--expand-to-other-buildings` | 选填 | flag | 允许跨楼推荐（同城，只有用户明确提出才传） |
| `--limit` | 选填 | int | 每页数量，默认 20，上限 100 |
| `--cursor` | 选填 | string | 分页游标 |

### 示例

```bash
# 查询明天上午空闲的会议室
wecom-cli meeting rooms search \
  --begin-time "2026-03-15 09:00:00" \
  --end-time "2026-03-15 12:00:00"

# 查询指定大楼、最小容量 10 人的会议室
wecom-cli meeting rooms search \
  --begin-time "2026-03-15 14:00:00" \
  --end-time "2026-03-15 15:00:00" \
  --building-name "A栋" \
  --min-capacity 10
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
