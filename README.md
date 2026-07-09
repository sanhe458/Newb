# Newb Shader — 三河修改版

> 一个基于 [Newb Shader](https://github.com/devendrn/newb-shader-mcbe) 的 Minecraft 基岩版光影包，在保留原版风格的基础上，对色彩、天空、水体与植被动效进行了重新调校。

**当前版本**：`v1.0.0` ｜ **最低引擎版本**：`1.16.100` ｜ **协议**：MIT License

---

## 特性一览

| 模块 | 调整内容 |
| --- | --- |
| **色彩校正** | 采用 ACES 色调映射，曝光 1.15、对比度 0.82、饱和度 1.25 |
| **天空** | 自定义天顶 / 地平线 / 夜空配色，支持日出日落渐变与极光效果 |
| **云层** | 移植自 Harrington Shader 的程序化云（单元哈希噪声、双层、按时段配色），可调尺寸、深度、速度与云阴影；雨天云量自动增大 |
| **光照** | 软阴影、火把闪烁、独立的白天 / 黄昏 / 夜晚光色 |
| **水体** | 水面波动、云层倒影、可调透明度与法线凹凸，区分海水 / 淡水 / 沼泽水色 |
| **水下** | 水下波动、柔和焦散、自定义水下亮度与雾色 |
| **植被动效** | 树叶与植物摆动、灯笼摇晃、雨天风力增强 |
| **雾与薄雾** | 平滑雾过渡，可调雾类型与薄雾密度 |

## 与原版的区别

- 着色器参数全面重新调校，视觉风格更柔和通透
- 色调映射由默认的 Extended Reinhard 切换为 ACES
- 天空、水体、光照配色按个人使用习惯调整
- 保留原版所有可配置项，便于进一步自定义

## 安装

1. 下载本仓库（`Code → Download ZIP`）或克隆：
   ```bash
   git clone https://github.com/sanhe458/Newb.git
   ```
2. 将整个文件夹放入基岩版资源包目录：
   ```
   games/com.mojang/resource_packs/
   ```
3. 启动游戏，在 `设置 → 全局资源` 中启用「Newb Shader 三河修改版」。

> 也可将文件夹重命名为 `.mcpack` 后双击导入。

## 自定义配置

所有用户可调参数集中在 [`shaders/glsl/config_utilities/`](shaders/glsl/config_utilities) 目录下，每个文件顶部以注释标明参数含义与取值范围：

| 文件 | 控制内容 |
| --- | --- |
| `global.h` | 时间翻转、光照强度、雾与薄雾 |
| `color.h` | 色调映射、曝光、对比度、饱和度、色调 |
| `sky.h` | 天空、天顶、地平线、水下雾色 |
| `clouds.h` | 云层参数与极光效果 |
| `terrain.h` | 地形光照、软阴影、波浪、水体、水下 |
| `extra.h` | 日月旋转、发光纹理、水纹细节 |

> 修改 `// Code starts here` 注释以下的内容可能导致渲染异常，请仅调整上方注释标记的参数。

更多自定义说明参见 [原项目文档](https://devendrn.github.io/newb-shader/customization.html)。

## 目录结构

```
.
├── shaders/glsl/          # GLSL 着色器源码
│   ├── config_utilities/  # 用户可调参数（首选项）
│   └── utilities/         # 噪声、检测等内部工具函数
├── materials/             # 材质定义
├── textures/              # 贴图资源
├── fogs/                  # 雾设置
├── biomes_client.json     # 生物群系水体颜色
└── manifest.json          # 资源包清单
```

## 致谢

- **[devendrn](https://github.com/devendrn)** — 原版 Newb Shader 作者
- **Miracle100KS — Harrington Shader** — 云层算法（`cloud_col`）移植来源
- Newb Shader 社区的所有贡献者

## License

沿用原项目的 [MIT License](LICENSE)。
