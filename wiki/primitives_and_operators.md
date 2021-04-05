# Primitives

## Constant

`constant(height: float) -> height, normal`

## Noise

`noise() -> height`

## Sine wave

```
sive_wave()
```

# Operations

## Color

`terrain | color(r: float[0, 1], g: float[0, 1], b: float[0, 1]) -> color, *`

## Distortion

`terrain | distortion(.amplitude: float(0, +inf], frequency: float(0, +inf]) -> height`

## Lerp

```
(terrain, terrain) | lerp(interpolant: float[0, 1])
```

## Max

`(terrain, terrain) | max(smooth: float(0, +inf]) -> color, height`

## Min

`(terrain, terrain) | min(smooth: float(0, +inf]) -> color, height`

## Scaling

```
terrain | scaling(xyz: float) -> *
terrain | scaling(x: float, y: float, z: float) -> *
terrain | scaling_xy(x: float, y: float) -> *
terrain | scaling_z(z: float) -> *
```

## Sum

```
(terrain, ...) | sum(xyz: float) -> height
```

## Translation

```
terrain | translation(x: float, y: float, z: float) -> *
terrain | translation_xy(x: float, y: float) -> *
terrain | translation_z(z: float) -> *
```
