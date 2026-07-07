# 水面波浪与颜色改进 - 产品需求文档

## Overview
- **Summary**: 改进 Minecraft 着色器包中的水面波浪效果和颜色表现，使其更加明显和美观
- **Purpose**: 用户反馈水面波浪几乎看不出来，颜色也不好看，需要增强视觉效果
- **Target Users**: 使用 Newb Shader 的 Minecraft 玩家

## Goals
- 增大水面波浪强度和可见范围，使波浪效果更加明显
- 改进水面颜色，使其更加生动、真实、美观
- 保持着色器的整体性能和兼容性

## Non-Goals (Out of Scope)
- 修改其他着色器效果（如天空、植物、灯笼等）
- 引入新的依赖或外部资源
- 改变整体着色器架构

## Background & Context
当前着色器包使用 GLSL 编写，水面波浪效果在 `terrain.vertex` 中实现，颜色定义在 `terrain.h` 中。波浪参数 `WATER_WAVE=0.02` 过小导致效果不明显，颜色值单调缺乏层次感。

## Functional Requirements
- **FR-1**: 增大水面波浪振幅，使其在更远距离可见
- **FR-2**: 扩展波浪效果的作用范围，从16单位增加到更远
- **FR-3**: 改进海水、淡水和沼泽水的颜色，使其更加美观
- **FR-4**: 增加水面波浪的动画细节，使其更加自然

## Non-Functional Requirements
- **NFR-1**: 保持着色器性能，不显著增加渲染开销
- **NFR-2**: 保持与现有材质和纹理的兼容性
- **NFR-3**: 保持跨平台兼容性（不同硬件配置）

## Constraints
- **Technical**: 使用现有 GLSL 着色器架构，不能引入新的渲染技术
- **Dependencies**: 依赖于现有的噪声函数和着色器常量

## Assumptions
- 用户使用的是支持 GLSL 的现代 GPU
- 用户期望更明显的视觉效果而非追求绝对真实感

## Acceptance Criteria

### AC-1: 波浪强度增加
- **Given**: 当前水面波浪振幅为0.02，作用范围为16单位
- **When**: 修改波浪参数
- **Then**: 波浪效果明显增强，在更远距离可见
- **Verification**: `human-judgment`

### AC-2: 水面颜色改进
- **Given**: 当前水面颜色为单调的蓝绿色
- **When**: 修改水面颜色参数
- **Then**: 水面颜色更加生动、有层次感
- **Verification**: `human-judgment`

### AC-3: 着色器性能保持
- **Given**: 修改后的着色器代码
- **When**: 在游戏中运行
- **Then**: 帧率保持在可接受范围内，无明显性能下降
- **Verification**: `human-judgment`

## Open Questions
- [ ] 是否需要增加波浪动画的频率？
- [ ] 是否需要调整水面反射效果以配合新颜色？
