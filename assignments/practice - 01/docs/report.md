# 《数据结构与算法2021秋》课程报告（实验一）

| 学号       | 姓名   | 得分 |
|------------|------|------|
| 120L021403 | 冯新航 |      |

## 食堂售饭问题

### 问题描述

假设某食堂有四个窗口对外售饭，从上午 `11:00` 开始到下午 `13:00` 结束。

由于某窗口在某个时间只能接待一个同学，因此在学生多的时候需要在窗口前排队，刚来的同学如果发现有空闲窗口即可上前买饭，反之若均有同学则要排到人数最少的窗口的后面。

现要设计一个算法模拟这种业务并计算一天中午饭同学在食堂的平均时间。

+ 输入格式

  以文件 `data.txt` 进行输入。
  
  第一行一个整数 `n` 表示窗口个数。

  接下来 `n` 行，每行一个字符串，表示窗口名称。

  接着是一个整数 `m` 表示学生人数。

  最后 `m` 行每行一个整数 `t` 和一个字符串 `s` ，分别表示学生的到达时间（从 `11:00` 起计算的秒数）和学生名字。

  学生进入食堂的时间满足 `11:00 - 13:00` 时间段的**正态分布**。

+ 输出格式

  + 文件输出：

    每行以事件的时间戳开头，表示学生进入食堂或打完饭的时间。接着是一段描述表明此时学生进入食堂选择哪个窗口或打完饭后窗口的信息。

  + 终端输出：

    一行，表示截至 `13:00` 所有学生的平均等待时间。

+ 输入样例

  ```bash
  3
  Window_1
  Window_2
  Window_3

  50
  393 Student_1
  1182 Student_2
  1684 Student_3
  2023 Student_4
  2296 Student_5
  2310 Student_6
  2477 Student_7
  2526 Student_8
  2673 Student_9
  2701 Student_10
  2775 Student_11
  2785 Student_12
  2872 Student_13
  2968 Student_14
  2974 Student_15
  3035 Student_16
  3113 Student_17
  3196 Student_18
  3198 Student_19
  3222 Student_20
  3258 Student_21
  3378 Student_22
  3443 Student_23
  3447 Student_24
  3454 Student_25
  3512 Student_26
  3584 Student_27
  3588 Student_28
  3640 Student_29
  3640 Student_30
  3656 Student_31
  3660 Student_32
  3687 Student_33
  3841 Student_34
  4046 Student_35
  4052 Student_36
  4155 Student_37
  4407 Student_38
  4421 Student_39
  4494 Student_40
  4540 Student_41
  4567 Student_42
  4630 Student_43
  4825 Student_44
  4981 Student_45
  5054 Student_46
  5170 Student_47
  5283 Student_48
  5608 Student_49
  6150 Student_50

  ```

+ 输出样例

  ```bash
  #result.txt
  [11:06:33] Student_1 同学在 Window_1 窗口排队打饭。
  [11:06:44] Student_1 同学在 Window_1 窗口打完饭，耗时 11秒，Window_1 窗口队伍长度： 0 。
  [11:19:42] Student_2 同学在 Window_1 窗口排队打饭。
  [11:19:54] Student_2 同学在 Window_1 窗口打完饭，耗时 12秒，Window_1 窗口队伍长度： 0 。
  [11:28:04] Student_3 同学在 Window_1 窗口排队打饭。
  [11:28:22] Student_3 同学在 Window_1 窗口打完饭，耗时 18秒，Window_1 窗口队伍长度： 0 。
  [11:33:43] Student_4 同学在 Window_1 窗口排队打饭。
  [11:34:13] Student_4 同学在 Window_1 窗口打完饭，耗时 30秒，Window_1 窗口队伍长度： 0 。
  [11:38:16] Student_5 同学在 Window_1 窗口排队打饭。
  [11:38:30] Student_6 同学在 Window_2 窗口排队打饭。
  [11:38:36] Student_5 同学在 Window_1 窗口打完饭，耗时 20秒，Window_1 窗口队伍长度： 0 。
  [11:38:49] Student_6 同学在 Window_2 窗口打完饭，耗时 19秒，Window_2 窗口队伍长度： 0 。
  [11:41:17] Student_7 同学在 Window_1 窗口排队打饭。
  [11:41:38] Student_7 同学在 Window_1 窗口打完饭，耗时 21秒，Window_1 窗口队伍长度： 0 。
  [11:42:06] Student_8 同学在 Window_1 窗口排队打饭。
  [11:42:36] Student_8 同学在 Window_1 窗口打完饭，耗时 30秒，Window_1 窗口队伍长度： 0 。
  [11:44:33] Student_9 同学在 Window_1 窗口排队打饭。
  [11:44:47] Student_9 同学在 Window_1 窗口打完饭，耗时 14秒，Window_1 窗口队伍长度： 0 。
  [11:45:01] Student_10 同学在 Window_1 窗口排队打饭。
  [11:45:15] Student_10 同学在 Window_1 窗口打完饭，耗时 14秒，Window_1 窗口队伍长度： 0 。
  [11:46:15] Student_11 同学在 Window_1 窗口排队打饭。
  [11:46:25] Student_12 同学在 Window_2 窗口排队打饭。
  [11:46:39] Student_11 同学在 Window_1 窗口打完饭，耗时 24秒，Window_1 窗口队伍长度： 0 。
  [11:46:47] Student_12 同学在 Window_2 窗口打完饭，耗时 22秒，Window_2 窗口队伍长度： 0 。
  [11:47:52] Student_13 同学在 Window_1 窗口排队打饭。
  [11:48:22] Student_13 同学在 Window_1 窗口打完饭，耗时 30秒，Window_1 窗口队伍长度： 0 。
  [11:49:28] Student_14 同学在 Window_1 窗口排队打饭。
  [11:49:34] Student_15 同学在 Window_2 窗口排队打饭。
  [11:49:51] Student_14 同学在 Window_1 窗口打完饭，耗时 23秒，Window_1 窗口队伍长度： 0 。
  [11:50:03] Student_15 同学在 Window_2 窗口打完饭，耗时 29秒，Window_2 窗口队伍长度： 0 。
  [11:50:35] Student_16 同学在 Window_1 窗口排队打饭。
  [11:50:52] Student_16 同学在 Window_1 窗口打完饭，耗时 17秒，Window_1 窗口队伍长度： 0 。
  [11:51:53] Student_17 同学在 Window_1 窗口排队打饭。
  [11:52:10] Student_17 同学在 Window_1 窗口打完饭，耗时 17秒，Window_1 窗口队伍长度： 0 。
  [11:53:16] Student_18 同学在 Window_1 窗口排队打饭。
  [11:53:18] Student_19 同学在 Window_2 窗口排队打饭。
  [11:53:39] Student_18 同学在 Window_1 窗口打完饭，耗时 23秒，Window_1 窗口队伍长度： 0 。
  [11:53:42] Student_20 同学在 Window_1 窗口排队打饭。
  [11:53:42] Student_19 同学在 Window_2 窗口打完饭，耗时 24秒，Window_2 窗口队伍长度： 0 。
  [11:53:59] Student_20 同学在 Window_1 窗口打完饭，耗时 17秒，Window_1 窗口队伍长度： 0 。
  [11:54:18] Student_21 同学在 Window_1 窗口排队打饭。
  [11:54:40] Student_21 同学在 Window_1 窗口打完饭，耗时 22秒，Window_1 窗口队伍长度： 0 。
  [11:56:18] Student_22 同学在 Window_1 窗口排队打饭。
  [11:56:29] Student_22 同学在 Window_1 窗口打完饭，耗时 11秒，Window_1 窗口队伍长度： 0 。
  [11:57:23] Student_23 同学在 Window_1 窗口排队打饭。
  [11:57:27] Student_24 同学在 Window_2 窗口排队打饭。
  [11:57:34] Student_25 同学在 Window_3 窗口排队打饭。
  [11:57:39] Student_24 同学在 Window_2 窗口打完饭，耗时 12秒，Window_2 窗口队伍长度： 0 。
  [11:57:44] Student_23 同学在 Window_1 窗口打完饭，耗时 21秒，Window_1 窗口队伍长度： 0 。
  [11:57:54] Student_25 同学在 Window_3 窗口打完饭，耗时 20秒，Window_3 窗口队伍长度： 0 。
  [11:58:32] Student_26 同学在 Window_1 窗口排队打饭。
  [11:58:43] Student_26 同学在 Window_1 窗口打完饭，耗时 11秒，Window_1 窗口队伍长度： 0 。
  [11:59:44] Student_27 同学在 Window_1 窗口排队打饭。
  [11:59:48] Student_28 同学在 Window_2 窗口排队打饭。
  [12:00:06] Student_27 同学在 Window_1 窗口打完饭，耗时 22秒，Window_1 窗口队伍长度： 0 。
  [12:00:15] Student_28 同学在 Window_2 窗口打完饭，耗时 27秒，Window_2 窗口队伍长度： 0 。
  [12:00:40] Student_29 同学在 Window_1 窗口排队打饭。
  [12:00:40] Student_30 同学在 Window_2 窗口排队打饭。
  [12:00:56] Student_31 同学在 Window_3 窗口排队打饭。
  [12:01:00] Student_32 同学在 Window_1 窗口排队打饭。
  [12:01:00] Student_29 同学在 Window_1 窗口打完饭，耗时 20秒，Window_1 窗口队伍长度： 1 。
  [12:01:04] Student_30 同学在 Window_2 窗口打完饭，耗时 24秒，Window_2 窗口队伍长度： 0 。
  [12:01:19] Student_32 同学在 Window_1 窗口打完饭，耗时 19秒，Window_1 窗口队伍长度： 0 。
  [12:01:26] Student_31 同学在 Window_3 窗口打完饭，耗时 30秒，Window_3 窗口队伍长度： 0 。
  [12:01:27] Student_33 同学在 Window_1 窗口排队打饭。
  [12:01:49] Student_33 同学在 Window_1 窗口打完饭，耗时 22秒，Window_1 窗口队伍长度： 0 。
  [12:04:01] Student_34 同学在 Window_1 窗口排队打饭。
  [12:04:24] Student_34 同学在 Window_1 窗口打完饭，耗时 23秒，Window_1 窗口队伍长度： 0 。
  [12:07:26] Student_35 同学在 Window_1 窗口排队打饭。
  [12:07:32] Student_36 同学在 Window_2 窗口排队打饭。
  [12:07:42] Student_36 同学在 Window_2 窗口打完饭，耗时 10秒，Window_2 窗口队伍长度： 0 。
  [12:07:52] Student_35 同学在 Window_1 窗口打完饭，耗时 26秒，Window_1 窗口队伍长度： 0 。
  [12:09:15] Student_37 同学在 Window_1 窗口排队打饭。
  [12:09:25] Student_37 同学在 Window_1 窗口打完饭，耗时 10秒，Window_1 窗口队伍长度： 0 。
  [12:13:27] Student_38 同学在 Window_1 窗口排队打饭。
  [12:13:40] Student_38 同学在 Window_1 窗口打完饭，耗时 13秒，Window_1 窗口队伍长度： 0 。
  [12:13:41] Student_39 同学在 Window_1 窗口排队打饭。
  [12:14:05] Student_39 同学在 Window_1 窗口打完饭，耗时 24秒，Window_1 窗口队伍长度： 0 。
  [12:14:54] Student_40 同学在 Window_1 窗口排队打饭。
  [12:15:18] Student_40 同学在 Window_1 窗口打完饭，耗时 24秒，Window_1 窗口队伍长度： 0 。
  [12:15:40] Student_41 同学在 Window_1 窗口排队打饭。
  [12:15:52] Student_41 同学在 Window_1 窗口打完饭，耗时 12秒，Window_1 窗口队伍长度： 0 。
  [12:16:07] Student_42 同学在 Window_1 窗口排队打饭。
  [12:16:25] Student_42 同学在 Window_1 窗口打完饭，耗时 18秒，Window_1 窗口队伍长度： 0 。
  [12:17:10] Student_43 同学在 Window_1 窗口排队打饭。
  [12:17:20] Student_43 同学在 Window_1 窗口打完饭，耗时 10秒，Window_1 窗口队伍长度： 0 。
  [12:20:25] Student_44 同学在 Window_1 窗口排队打饭。
  [12:20:49] Student_44 同学在 Window_1 窗口打完饭，耗时 24秒，Window_1 窗口队伍长度： 0 。
  [12:23:01] Student_45 同学在 Window_1 窗口排队打饭。
  [12:23:12] Student_45 同学在 Window_1 窗口打完饭，耗时 11秒，Window_1 窗口队伍长度： 0 。
  [12:24:14] Student_46 同学在 Window_1 窗口排队打饭。
  [12:24:27] Student_46 同学在 Window_1 窗口打完饭，耗时 13秒，Window_1 窗口队伍长度： 0 。
  [12:26:10] Student_47 同学在 Window_1 窗口排队打饭。
  [12:26:29] Student_47 同学在 Window_1 窗口打完饭，耗时 19秒，Window_1 窗口队伍长度： 0 。
  [12:28:03] Student_48 同学在 Window_1 窗口排队打饭。
  [12:28:24] Student_48 同学在 Window_1 窗口打完饭，耗时 21秒，Window_1 窗口队伍长度： 0 。
  [12:33:28] Student_49 同学在 Window_1 窗口排队打饭。
  [12:33:44] Student_49 同学在 Window_1 窗口打完饭，耗时 16秒，Window_1 窗口队伍长度： 0 。
  [12:42:30] Student_50 同学在 Window_1 窗口排队打饭。
  [12:42:42] Student_50 同学在 Window_1 窗口打完饭，耗时 12秒，Window_1 窗口队伍长度： 0 。

  ```

  ```bash
  #终端输出
  学生平均等待时间：19.24秒
  详细排队信息已输出至 result.txt
  ```

### 解决方案

[`restaurant.cpp`](data-generator.cpp) 包含了全部解决方案。

+ 流程图

  ![flowchart](img/flowchart.jpg)

+ UML图:

  ![uml.jpg](img/uml.jpg)

#### `Student` 类

包含学生的基本信息及其等待时间，通过两个接口 `void setStartWaitingTime(int startWaitingTime);` 和 `int getStartWaitingTime();` 设置和获取学生开始等待的时间。

#### `SellWindow` 类

模拟窗口的打饭操作，设置等待队列 `waitingQueue` 模拟学生排队。每次打饭操作耗时在 `[20, 40]` 内随机选取，每秒减少 `1` ，当剩余时间为 `0` 时弹出队首学生，表明打饭完成，同时统计该学生的等待时间并输出 `log`。

#### `Restaurant` 类

模拟饭堂整体运行情况。

首先将所有学生及窗口信息读入。

饭堂运行时，调用 `run()` 方法，启用一个大循环，每次循环调用 `update()` 函数，触发时间流逝、学生进入饭堂、选择一个窗口，遍历窗口执行打饭动作。

+ `void studentAllocate();`：分配执行学生分配。
+ `void windowBalanceLoader(const Student &student);`：按规则为每个学生选择窗口，实现窗口的**均衡负载**。
+ `void sellWindowsOfferService();`：依次调用每个 `SellWindow` 的 `offerService()` 方法执行打饭动作。

当 `currentTime` 超过 `endTime` 时，运行结束，统计学生的平均等待时间。

#### `IO.h`

包含自定义的工具类 `IO` 类，提供重定向输入输出流的快捷方式。

#### `Random.h`

包含定义的工具类 `Random` ，提供生成 `int` 范围内伪随机数生成的快捷方式。

### 数据生成器

[`data-generator.cpp`](data-generator.cpp) 用于生成一组合法的数据，尤其是生成 `11:00 - 13:00` 内满足正态分布的学生进入饭堂时间。

通过调整 `countOfWindows` 与 `countOfStudents` 的值，可以调整窗口与学生的数量:

```cpp
int countOfWindows = 20;
int countOfStudents = 5000;
```

经测试，若饭堂有 `20` 个窗口， `5000` 名学生陆续进入用餐时，高峰期队伍长度可超过 `50`、等待时间可超过 `1000s` 、平均等待时间约 `600s` 。
