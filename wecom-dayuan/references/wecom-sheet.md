# 企微在线表格

使用 wecom-cli 操作在线表格（非智能表格）。

## 探索命令

不确定命令参数时，使用 `--help` 或 `--schema` 自行探索：

```bash
# 查看模块下的所有子命令
wecom-cli sheet --help

# 查看某个命令的详细参数 schema
wecom-cli sheet create --schema
wecom-cli sheet ranges get --schema
```

> **原则**：文档可能过时，遇到不确定的参数，用 `--schema` 获取最新定义。

---

## 命令列表

| 命令 | 说明 |
|------|------|
| `sheet create` | 创建在线表格 |
| `sheet get` | 获取表格信息 |
| `sheet import` | 从文件导入创建表格 |
| `sheet ranges get` | 读取单元格数据 |
| `sheet contents update` | 更新单元格数据 |
| `sheet rows append` | 追加行 |
| `sheet subsheets add` | 添加子表 |
| `sheet subsheets delete` | 删除子表 |

---

## sheet create - 创建在线表格

创建空白在线表格。

```bash
wecom-cli sheet create --sheet-name <表格名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--sheet-name` | **必填** | string | 表格名称 |
| `--space-id` | 选填 | string | 知识空间 ID（不传则创建到个人空间） |

### 示例

```bash
wecom-cli sheet create --sheet-name "数据统计表"
```

---

## sheet get - 获取表格信息

获取表格元信息，包括子表列表、更新时间等。

```bash
wecom-cli sheet get --docid <文档ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |

### 示例

```bash
wecom-cli sheet get --docid "sheet_123"
```

---

## sheet import - 从文件导入创建表格

从 Excel/CSV 文件导入创建在线表格。

```bash
wecom-cli sheet import --input <文件路径> --sheet-name <表格名称> [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--input` | **必填** | string | 文件路径（xlsx/csv） |
| `--sheet-name` | **必填** | string | 表格名称 |
| `--space-id` | 选填 | string | 知识空间 ID |

### 示例

```bash
wecom-cli sheet import --input ./data.xlsx --sheet-name "导入的表格"
```

---

## sheet ranges get - 读取单元格数据

读取指定范围的单元格数据。

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `docid` | **必填** | string | 文档 ID（`e3_` 开头的普通表格）|
| `sheet_id` | **必填** | string | 子表 ID（先用 `sheet-get` 获取）|
| `range` | 选填 | string | 读取范围，如 `A1:C10`。不传则读取全部数据 |
| `mode` | 选填 | string | 返回格式：`csv` 或 `default` |

### 示例

```bash
# 先获取子表列表
dayuan-auth exec wecom sheet-get --json '{"docid": "e3_xxx"}'

# 读取指定范围
dayuan-auth exec wecom sheet-read --json '{
  "docid": "e3_xxx",
  "sheet_id": "BB08J2",
  "range": "A1:D100"
}'
```

### 返回格式

返回 `data.content` 是 CSV 格式字符串，用 `\r\n` 分隔行，`,` 分隔列。

---

## sheet contents update - 更新单元格数据

更新指定范围的单元格数据。

```bash
wecom-cli sheet contents update --docid <文档ID> --data '<json>' [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--data` | **必填** | json | 写入的数据，二维数组格式 |
| `--subsheet-id` | 选填 | string | 子表 ID（不传默认第一个子表） |
| `--start-cell` | 选填 | string | 起始单元格，如 `A1`。默认 `A1` |

### 示例

```bash
# 从 A1 开始写入数据
wecom-cli sheet contents update --docid "sheet_123" \
  --data '[["姓名", "年龄"], ["张三", 25], ["李四", 30]]'

# 从指定位置写入
wecom-cli sheet contents update --docid "sheet_123" \
  --subsheet-id "sub_1" \
  --start-cell "C5" \
  --data '[["新数据1", "新数据2"]]'
```

---

## sheet rows append - 追加行

在表格末尾追加行数据。

```bash
wecom-cli sheet rows append --docid <文档ID> --data '<json>' [OPTIONS]
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--data` | **必填** | json | 追加的行数据，二维数组格式 |
| `--subsheet-id` | 选填 | string | 子表 ID（不传默认第一个子表） |

### 示例

```bash
# 追加两行数据
wecom-cli sheet rows append --docid "sheet_123" \
  --data '[["王五", 28], ["赵六", 35]]'
```

---

## sheet subsheets add - 添加子表

在表格中添加新的子表（Sheet）。

```bash
wecom-cli sheet subsheets add --docid <文档ID> --title <子表名称>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--title` | **必填** | string | 子表名称 |

### 示例

```bash
wecom-cli sheet subsheets add --docid "sheet_123" --title "Sheet2"
```

---

## sheet subsheets delete - 删除子表

删除表格中的子表。

```bash
wecom-cli sheet subsheets delete --docid <文档ID> --subsheet-id <子表ID>
```

### 参数

| 参数 | 必填 | 类型 | 说明 |
|------|:----:|------|------|
| `--docid` | **必填** | string | 文档 ID |
| `--subsheet-id` | **必填** | string | 子表 ID |

### 示例

```bash
wecom-cli sheet subsheets delete --docid "sheet_123" --subsheet-id "sub_2"
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
