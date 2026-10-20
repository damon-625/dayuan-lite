# 企微智能表格（SmartSheet）

使用 wecom-cli 操作智能表格（类 Airtable/飞书多维表格）。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli smartsheet --help
wecom-cli smartsheet records --help
wecom-cli smartsheet fields --help

# 查看某个命令的详细参数 schema
wecom-cli smartsheet records list --schema
wecom-cli smartsheet fields add --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

### 表格管理
| 命令 | 说明 |
|------|------|
| `smartsheet create` | 创建智能表格 |
| `smartsheet get` | 获取表格信息 |
| `smartsheet import` | 从文件导入创建表格 |

### 子表管理
| 命令 | 说明 |
|------|------|
| `smartsheet sheets list` | 获取子表列表 |
| `smartsheet sheets add` | 添加子表 |
| `smartsheet sheets delete` | 删除子表 |
| `smartsheet sheets update` | 更新子表属性 |

### 字段管理
| 命令 | 说明 |
|------|------|
| `smartsheet fields list` | 获取字段列表 |
| `smartsheet fields add` | 添加字段 |
| `smartsheet fields update` | 更新字段属性 |
| `smartsheet fields delete` | 删除字段 |

### 记录管理
| 命令 | 说明 |
|------|------|
| `smartsheet records list` | 查询记录 |
| `smartsheet records add` | 新增记录 |
| `smartsheet records update` | 更新记录 |
| `smartsheet records delete` | 删除记录 |

### 视图管理
| 命令 | 说明 |
|------|------|
| `smartsheet views list` | 获取视图列表 |
| `smartsheet views add` | 添加视图 |
| `smartsheet views delete` | 删除视图 |

### 图表
| 命令 | 说明 |
|------|------|
| `smartsheet charts get` | 获取图表数据 |

### 附件
| 命令 | 说明 |
|------|------|
| `smartsheet images upload` | 上传图片 |
| `smartsheet files upload` | 上传文件 |

---

## smartsheet create - 创建智能表格

创建空白智能表格。

```bash
wecom-cli smartsheet create --doc-name <表格名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--doc-name` | **必填** | string | 表格名称 |
| `--space-id` | 选填 | string | 知识空间 ID（不传则创建到个人空间） |

### 示例

```bash
wecom-cli smartsheet create --doc-name "任务管理"
```

---

## smartsheet get - 获取表格信息

获取表格元信息。

```bash
wecom-cli smartsheet get --docid <文档ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |

### 示例

```bash
wecom-cli smartsheet get --docid "ss_123"
```

---

## smartsheet import - 从文件导入创建表格

从 Excel/CSV 文件导入创建智能表格。

```bash
wecom-cli smartsheet import --input <文件路径> --doc-name <表格名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--input` | **必填** | string | 文件路径（xlsx/csv） |
| `--doc-name` | **必填** | string | 表格名称 |
| `--space-id` | 选填 | string | 知识空间 ID |

### 示例

```bash
wecom-cli smartsheet import --input ./data.xlsx --doc-name "导入的智能表格"
```

---

## smartsheet sheets list - 获取子表列表

获取智能表格中的子表列表。

```bash
wecom-cli smartsheet sheets list --docid <文档ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |

### 示例

```bash
wecom-cli smartsheet sheets list --docid "ss_123"
```

---

## smartsheet sheets add - 添加子表

在智能表格中添加新的子表。

```bash
wecom-cli smartsheet sheets add --docid <文档ID> --sheet-name <子表名称>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-name` | **必填** | string | 子表名称 |

### 示例

```bash
wecom-cli smartsheet sheets add --docid "ss_123" --sheet-name "新子表"
```

---

## smartsheet sheets delete - 删除子表

删除智能表格中的子表。

```bash
wecom-cli smartsheet sheets delete --docid <文档ID> --sheet-id <子表ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |

### 示例

```bash
wecom-cli smartsheet sheets delete --docid "ss_123" --sheet-id "sheet_456"
```

---

## smartsheet sheets update - 更新子表属性

更新子表属性（如名称）。

```bash
wecom-cli smartsheet sheets update --docid <文档ID> --sheet-id <子表ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--sheet-name` | 选填 | string | 新名称 |

### 示例

```bash
wecom-cli smartsheet sheets update --docid "ss_123" --sheet-id "sheet_456" --sheet-name "新名称"
```

---

## smartsheet fields list - 获取字段列表

获取子表的字段（列）定义。

```bash
wecom-cli smartsheet fields list --docid <文档ID> --sheet-id <子表ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |

### 示例

```bash
wecom-cli smartsheet fields list --docid "ss_123" --sheet-id "sheet_456"
```

---

## smartsheet fields add - 添加字段

在子表中添加新字段（列）。

```bash
wecom-cli smartsheet fields add --docid <文档ID> --sheet-id <子表ID> --field-title <字段名> --field-type <字段类型>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--field-title` | **必填** | string | 字段名称 |
| `--field-type` | **必填** | string | 字段类型 |
| `--options` | 选填 | json | 字段选项（单选/多选字段需要） |

**常用字段类型**：
- `TEXT`: 文本
- `NUMBER`: 数字
- `SINGLE_SELECT`: 单选
- `MULTI_SELECT`: 多选
- `DATE`: 日期
- `CHECKBOX`: 复选框
- `URL`: 链接
- `ATTACHMENT`: 附件
- `FORMULA`: 公式
- `REFERENCE`: 关联

### 示例

```bash
# 添加文本字段
wecom-cli smartsheet fields add --docid "ss_123" --sheet-id "sheet_456" \
  --field-title "备注" --field-type TEXT

# 添加单选字段
wecom-cli smartsheet fields add --docid "ss_123" --sheet-id "sheet_456" \
  --field-title "状态" --field-type SINGLE_SELECT \
  --options '{"options": [{"name": "待处理"}, {"name": "进行中"}, {"name": "已完成"}]}'
```

---

## smartsheet fields update - 更新字段属性

更新字段属性（如名称、选项等）。

```bash
wecom-cli smartsheet fields update --docid <文档ID> --sheet-id <子表ID> --field-id <字段ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--field-id` | **必填** | string | 字段 ID |
| `--field-title` | 选填 | string | 新名称 |
| `--options` | 选填 | json | 更新选项 |

### 示例

```bash
wecom-cli smartsheet fields update --docid "ss_123" --sheet-id "sheet_456" \
  --field-id "fld_789" --field-title "新字段名"
```

---

## smartsheet fields delete - 删除字段

删除子表中的字段。

```bash
wecom-cli smartsheet fields delete --docid <文档ID> --sheet-id <子表ID> --field-id <字段ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--field-id` | **必填** | string | 字段 ID |

### 示例

```bash
wecom-cli smartsheet fields delete --docid "ss_123" --sheet-id "sheet_456" --field-id "fld_789"
```

---

## smartsheet records list - 查询记录

查询子表中的记录。支持过滤、排序、分页。

```bash
wecom-cli smartsheet records list --docid <文档ID> --sheet-id <子表ID> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--view-id` | 选填 | string | 视图 ID（应用视图的过滤和排序） |
| `--record-ids` | 选填 | string[] | 指定记录 ID 列表 |
| `--filter` | 选填 | json | 过滤条件 |
| `--filter-spec` | 选填 | json | 过滤设置（更详细的过滤配置） |
| `--sort` | 选填 | json_array | 排序配置 |
| `--key-type` | 选填 | string | 返回的字段键类型：`field_id`（默认）或 `field_title` |
| `--type` | 选填 | string | 数据类型，如 `render` 表示返回渲染后的值 |
| `--is-smartagent` | 选填 | flag | 是否按 SmartAgent 场景处理 |
| `--sql` | 选填 | string[] | SQL 语句列表（SmartAgent 场景） |
| `--offset` | 选填 | int | 分页偏移量 |
| `--limit` | 选填 | int | 每页记录数，默认 100 |

### 示例

```bash
# 查询全部记录
wecom-cli smartsheet records list --docid "ss_123" --sheet-id "sheet_456"

# 查询指定记录
wecom-cli smartsheet records list --docid "ss_123" --sheet-id "sheet_456" \
  --record-ids "rec_1" "rec_2"

# 使用过滤条件
wecom-cli smartsheet records list --docid "ss_123" --sheet-id "sheet_456" \
  --filter '{"field_id": "fld_status", "operator": "is", "value": "进行中"}'

# 返回字段标题而非 ID
wecom-cli smartsheet records list --docid "ss_123" --sheet-id "sheet_456" \
  --key-type field_title
```

---

## smartsheet records add - 新增记录

在子表中新增记录。

```bash
wecom-cli smartsheet records add --docid <文档ID> --sheet-id <子表ID> --records '<json_array>' [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--records` | **必填** | json_array | 记录数组，每条记录是 `{field_id: value}` 或 `{field_title: value}` 的对象 |
| `--key-type` | 选填 | string | 字段键类型：`field_id`（默认）或 `field_title` |
| `--type` | 选填 | string | 操作类型 |

### 示例

```bash
# 使用 field_id
wecom-cli smartsheet records add --docid "ss_123" --sheet-id "sheet_456" \
  --records '[{"fld_name": "张三", "fld_status": "待处理"}]'

# 使用 field_title
wecom-cli smartsheet records add --docid "ss_123" --sheet-id "sheet_456" \
  --key-type field_title \
  --records '[{"姓名": "张三", "状态": "待处理"}]'
```

---

## smartsheet records update - 更新记录

更新子表中的记录。

```bash
wecom-cli smartsheet records update --docid <文档ID> --sheet-id <子表ID> --records '<json_array>' [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--records` | **必填** | json_array | 更新记录数组，必须包含 `record_id` 字段 |
| `--key-type` | 选填 | string | 字段键类型 |

### 示例

```bash
wecom-cli smartsheet records update --docid "ss_123" --sheet-id "sheet_456" \
  --records '[{"record_id": "rec_1", "fld_status": "已完成"}]'
```

---

## smartsheet records delete - 删除记录

删除子表中的记录。

```bash
wecom-cli smartsheet records delete --docid <文档ID> --sheet-id <子表ID> --record-ids <记录ID列表>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--record-ids` | **必填** | string[] | 记录 ID 列表 |

### 示例

```bash
wecom-cli smartsheet records delete --docid "ss_123" --sheet-id "sheet_456" \
  --record-ids "rec_1" "rec_2"
```

---

## smartsheet views list - 获取视图列表

获取子表的视图列表。

```bash
wecom-cli smartsheet views list --docid <文档ID> --sheet-id <子表ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |

### 示例

```bash
wecom-cli smartsheet views list --docid "ss_123" --sheet-id "sheet_456"
```

---

## smartsheet views add - 添加视图

在子表中添加新视图。

```bash
wecom-cli smartsheet views add --docid <文档ID> --sheet-id <子表ID> --view-name <视图名称> --view-type <视图类型>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--view-name` | **必填** | string | 视图名称 |
| `--view-type` | **必填** | string | 视图类型：`GRID`（表格）、`KANBAN`（看板）、`GALLERY`（画廊）、`CALENDAR`（日历）、`GANTT`（甘特图） |

### 示例

```bash
wecom-cli smartsheet views add --docid "ss_123" --sheet-id "sheet_456" \
  --view-name "看板视图" --view-type KANBAN
```

---

## smartsheet views delete - 删除视图

删除子表中的视图。

```bash
wecom-cli smartsheet views delete --docid <文档ID> --sheet-id <子表ID> --view-id <视图ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--sheet-id` | **必填** | string | 子表 ID |
| `--view-id` | **必填** | string | 视图 ID |

### 示例

```bash
wecom-cli smartsheet views delete --docid "ss_123" --sheet-id "sheet_456" --view-id "view_789"
```

---

## smartsheet charts get - 获取图表数据

获取智能表格中的图表数据。

```bash
wecom-cli smartsheet charts get --docid <文档ID> --chart-id <图表ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--chart-id` | **必填** | string | 图表 ID |

### 示例

```bash
wecom-cli smartsheet charts get --docid "ss_123" --chart-id "chart_456"
```

---

## smartsheet images upload - 上传图片

上传图片到智能表格，返回图片 URL 供附件字段使用。

```bash
wecom-cli smartsheet images upload --docid <文档ID> --input <文件路径>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--input` | **必填** | string | 图片文件路径 |

### 示例

```bash
wecom-cli smartsheet images upload --docid "ss_123" --input ./photo.jpg
```

---

## smartsheet files upload - 上传文件

上传文件到智能表格，返回文件 URL。

```bash
wecom-cli smartsheet files upload --docid <文档ID> --input <文件路径>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--input` | **必填** | string | 文件路径 |

### 示例

```bash
wecom-cli smartsheet files upload --docid "ss_123" --input ./document.pdf
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
| `--page-count <n>` | 分页拉取页数 |
| `--page-delay <ms>` | 分页请求间隔（默认 100ms） |
