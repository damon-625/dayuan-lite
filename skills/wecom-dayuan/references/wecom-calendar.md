# 企微日历日程管理

使用 wecom-cli 管理日程。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli calendar --help
wecom-cli calendar schedules --help

# 查看某个命令的详细参数 schema
wecom-cli calendar schedules create --schema
wecom-cli calendar schedules free list --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `calendar schedules list` | 查询日程列表 |
| `calendar schedules get` | 批量获取日程详情 |
| `calendar schedules create` | 创建日程 |
| `calendar schedules update` | 更新日程 |
| `calendar schedules cancel` | 取消日程 |
| `calendar schedules search` | 搜索日程 |
| `calendar schedules free list` | 查询空闲时段 |

---

## calendar schedules list - 查询日程列表

查询指定时间范围内的日程列表。

```bash
wecom-cli calendar schedules list [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--begin-time` | 选填 | string | 查询范围开始时间，格式：`YYYY-MM-DD HH:mm:ss`。不传默认当前时间 |
| `--end-time` | 选填 | string | 查询范围结束时间，格式：`YYYY-MM-DD HH:mm:ss`。不传默认开始时间 +30 天 |

### 示例

```bash
# 查询未来一周的日程
wecom-cli calendar schedules list --begin-time "2026-03-01 00:00:00" --end-time "2026-03-07 23:59:59"
```

---

## calendar schedules get - 批量获取日程详情

根据日程 ID 批量获取日程详情。

```bash
wecom-cli calendar schedules get --schedule-ids <id1> <id2> ...
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--schedule-ids` | **必填** | string[] | 日程 ID 列表 |

### 示例

```bash
wecom-cli calendar schedules get --schedule-ids "sch_123" "sch_456"
```

---

## calendar schedules create - 创建日程

创建日程，支持设置标题、时间、地点、备注、参与人等。

```bash
wecom-cli calendar schedules create --subject <标题> --begin-time <开始时间> --end-time <结束时间> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--subject` | **必填** | string | 日程标题 |
| `--begin-time` | **必填** | string | 开始时间，格式：`YYYY-MM-DD HH:mm:ss` |
| `--end-time` | **必填** | string | 结束时间，格式：`YYYY-MM-DD HH:mm:ss` |
| `--attendees` | 选填 | json_array | 参与人列表，格式：`[{"userid": "xxx"}, ...]` |
| `--location` | 选填 | string | 地点 |
| `--description` | 选填 | string | 备注 |
| `--is-all-day` | 选填 | flag | 是否全天日程，默认 false |
| `--meeting-room-id` | 选填 | string | 会议室 ID，传入会预定会议室 |
| `--reminders` | 选填 | json | 提醒时间差值（秒），默认 `[-900]`（提前 15 分钟） |
| `--repeat-rule` | 选填 | json | 周期规则，`is_repeat=false` 时按非周期日程创建 |
| `--timezone` | 选填 | json | 时区信息 |
| `--allow-self-join` | 选填 | flag | 是否允许主动加入，默认 true |
| `--mark-optional-attendees` | 选填 | string[] | 标记可选参与人 |

### 示例

```bash
# 创建简单日程
wecom-cli calendar schedules create \
  --subject "项目评审会" \
  --begin-time "2026-03-15 14:00:00" \
  --end-time "2026-03-15 15:00:00"

# 创建带参与人和地点的日程
wecom-cli calendar schedules create \
  --subject "周会" \
  --begin-time "2026-03-15 10:00:00" \
  --end-time "2026-03-15 11:00:00" \
  --attendees '[{"userid": "user1"}, {"userid": "user2"}]' \
  --location "会议室A" \
  --description "每周例会"
```

---

## calendar schedules update - 更新日程

更新日程信息（Patch 语义），支持修改标题、时间、地点、参与人等。

```bash
wecom-cli calendar schedules update --schedule-id <日程ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--schedule-id` | **必填** | string | 日程 ID |
| `--subject` | 选填 | string | 新标题 |
| `--begin-time` | 选填 | string | 新开始时间 |
| `--end-time` | 选填 | string | 新结束时间 |
| `--location` | 选填 | string | 新地点，传空字符串表示清空 |
| `--description` | 选填 | string | 新备注，传空字符串表示清空 |
| `--is-all-day` | 选填 | flag | 是否全天 |
| `--meeting-room-id` | 选填 | string | 会议室 ID |
| `--add-attendees` | 选填 | json_array | 新增的参与人列表 |
| `--remove-attendees` | 选填 | json_array | 移除的参与人列表 |
| `--allow-self-join` | 选填 | flag | 是否允许主动加入 |
| `--repeat-mod` | 选填 | json | 周期编辑规则（周期日程必填） |

### 示例

```bash
# 修改日程标题和时间
wecom-cli calendar schedules update \
  --schedule-id "sch_123" \
  --subject "新标题" \
  --begin-time "2026-03-15 15:00:00" \
  --end-time "2026-03-15 16:00:00"

# 添加和移除参与人
wecom-cli calendar schedules update \
  --schedule-id "sch_123" \
  --add-attendees '[{"userid": "user3"}]' \
  --remove-attendees '[{"userid": "user1"}]'
```

---

## calendar schedules cancel - 取消日程

取消（删除）日程，周期日程需指定编辑规则。

```bash
wecom-cli calendar schedules cancel --schedule-id <日程ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--schedule-id` | **必填** | string | 日程 ID |
| `--repeat-mod` | 选填 | json | 周期编辑规则（周期日程必填）。枚举：`this`（仅本次）、`future`（本次及以后）、`all`（全部） |

### 示例

```bash
# 取消单次日程
wecom-cli calendar schedules cancel --schedule-id "sch_123"

# 取消周期日程的单次
wecom-cli calendar schedules cancel --schedule-id "sch_123" --repeat-mod '{"edit_type": "this"}'
```

---

## calendar schedules search - 搜索日程

按关键词搜索指定时间范围内的日程。

```bash
wecom-cli calendar schedules search [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--keywords` | 选填* | string[] | 搜索关键词（关键词、组织人、参与人至少传其一） |
| `--organizer` | 选填* | string | 组织人 userid |
| `--has-attendees` | 选填* | json_array | 参与人列表 |
| `--begin-time` | 选填 | string | 开始时间 |
| `--end-time` | 选填 | string | 结束时间 |
| `--limit` | 选填 | int | 返回最大日程数，默认 10，最大 1000 |
| `--cursor` | 选填 | string | 分页游标 |

### 示例

```bash
# 按关键词搜索
wecom-cli calendar schedules search --keywords "周会" "评审"

# 搜索某人组织的日程
wecom-cli calendar schedules search --organizer "user1" --begin-time "2026-03-01 00:00:00"
```

---

## calendar schedules free list - 查询空闲时段

查询指定成员在指定时间范围内的共同空闲时段。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `userids` | **必填** | string[] | 成员 userid 列表，1+ 个成员 |
| `begin_time` | **必填** | string | 查询窗口起始时间 |
| `end_time` | **必填** | string | 查询窗口结束时间，必须晚于 begin_time 且晚于当前时间 |
| `min_duration_minutes` | 选填 | int | 最小空闲时长（分钟），默认 30 |
| `limit` | 选填 | int | 返回数量，默认 10 |
| `strategy` | 选填 | string | 策略，默认 `max_attendees` |

### 示例

```bash
# 查询两人的共同空闲时段
dayuan-auth exec wecom calendar-free-list --json '{
  "userids": ["wo65jOUwAAD1qicpBLyDRIbuiuFBkHJA", "wo65jOUwAAq0wZl5XiLr22gcQZeodplg"],
  "begin_time": "2026-10-21 09:00:00",
  "end_time": "2026-10-21 18:00:00",
  "min_duration_minutes": 60
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
