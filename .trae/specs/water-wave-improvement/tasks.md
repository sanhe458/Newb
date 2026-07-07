# 水面波浪与颜色改进 - 实现计划

## [x] Task 1: 增大水面波浪振幅和作用范围
- **Priority**: high
- **Depends On**: None
- **Description**: 
  - 修改 `WATER_WAVE` 参数从 0.02 增加到更大的值（如 0.08-0.12）
  - 增加波浪效果的作用范围从 16 单位到更大的距离（如 32 单位）
  - 调整波浪动画的细节，使其更加自然明显
- **Acceptance Criteria Addressed**: AC-1
- **Test Requirements**:
  - `human-judgement` TR-1.1: 波浪效果明显增强，在更远距离可见
  - `human-judgement` TR-1.2: 波浪动画流畅自然，无突兀感

## [x] Task 2: 改进水面颜色
- **Priority**: high
- **Depends On**: None
- **Description**: 
  - 修改海水颜色（sea_water_color）使其更加生动有层次感
  - 修改淡水颜色（fresh_water_color）使其更加清澈自然
  - 修改沼泽水颜色（marshy_water_color）使其更加真实
  - 考虑增加颜色随时间变化的效果（日出/日落时的颜色变化）
- **Acceptance Criteria Addressed**: AC-2
- **Test Requirements**:
  - `human-judgement` TR-2.1: 水面颜色更加美观，有层次感
  - `human-judgement` TR-2.2: 不同类型的水面（海水/淡水/沼泽）颜色区分明显

## [x] Task 3: 调整水面反射和光照效果
- **Priority**: medium
- **Depends On**: Task 2
- **Description**: 
  - 调整水面反射效果以配合新的颜色配置
  - 优化水面光照计算，使颜色更加生动
  - 调整水面透明度以增强视觉效果
- **Acceptance Criteria Addressed**: AC-2
- **Test Requirements**:
  - `human-judgement` TR-3.1: 水面反射与新颜色配合良好
  - `human-judgement` TR-3.2: 水面光照效果自然

## [x] Task 4: 性能验证
- **Priority**: low
- **Depends On**: Task 1, Task 2, Task 3
- **Description**: 
  - 确保修改后的着色器性能保持在可接受范围内
  - 检查是否有明显的帧率下降
- **Acceptance Criteria Addressed**: AC-3
- **Test Requirements**:
  - `human-judgement` TR-4.1: 游戏运行流畅，无明显卡顿
  - `human-judgement` TR-4.2: 帧率保持在可接受范围内
