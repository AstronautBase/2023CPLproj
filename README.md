# Astronaut's running game

## 平台
- 操作系统 **Windows 11**  
- IDE **VSCode1.85.2(user setup)**

## C语言环境
- gcc 12.3.0
- x86_64-w64-mingw32

## 编译选项
默认

## 第三方库
未使用

## 游戏内容
### 各字符含义
- **o** 玩家
- **U** 需要上跳的障碍物
- **D** 需要下蹲的障碍物
- **$** 金币
- **@** 无敌星 —— 获取后4步内无视障碍物
### 操作
- __W__ 上跳
- __S__ 下蹲
- __A__ 左移
- __D__ 右移
### 玩家状态
- **running** 奔跑状态
- **jumping** 跳跃状态
- **crouching** 下蹲状态
- **invincible** 无敌状态
### 玩法及注意事项
1. 玩家通过按键控制游戏人物移动或调整状态
2. 当游戏人物处于跳跃jumping/下蹲crouching状态时,若下一步不进行其他操作,默认回到奔跑running状态
3. 游戏中每一帧可对游戏人物操作两次,比如：连按'A'两次，可让游戏人物向左移动两格
4. 游戏中途按**Esc**键可强制退出；按**空格键**可暂停，后按任意键继续游戏
5. 在每轮游戏结束时，有得分界面，维持3秒
6. 在每轮游戏开始界面，按**Enter**开始游戏，按**Esc**退出游戏
7. **得分方式**：每获取一个'$'得50分；每通过一个障碍得100分
8. **游戏速度共分四档**，得分达到1000/2000/4000时会加速

## 感想
原本想着自己对游戏兴趣不大，不如选择“较为简单的客观题”。在SQL挣扎了数天后进度缓慢，看着ddl的逼近人也逐渐焦虑，沉下心来经过谨慎考虑，决定在时间过半时切换赛道，从0开始学习命令行游戏制作的知识。也迈过了i人的坎，数次向已经制作完成的同学求助以及吸取经验，最后还是较为顺利的制作出了这个非常简陋的跑酷游戏，也发掘了些许做游戏的乐趣。当把.exe文件发给朋友们测试时他们的反馈让我很有成就感，也从其中获取了一些宝贵的修改建议。  
最后就在此感谢在整个项目完成过程以及这个学期中为我提供过帮助的老师、助教、朋友们，虽然这个从0开始学习的路走得异常艰难，机试分数也很不理想，所幸还是得到了迅速的成长，希望今后能在这条路上继续走下去。