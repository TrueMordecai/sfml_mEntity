# Desription

This is a small class that aim to help with the animation of sprite with sfml
Can be easily adapted to CSFML
The main show a little exemple on how to use it

# Usage

The main class is mEntity, you can initialize it like this

```cpp
mEntity entity("sprite.png", {22, 187, 17, 29}, 120, 6, LEFT_TO_RIGHT, "walk");
entity.addAnimationLoop("idle", 3, 500, {21, 68, 16, 23});
```

The animations are saved and can be call later on the program

```cpp
entity.changeAnimationLoop("walk");
```
![Capture vidéo du 2024-06-11 08-45-34](https://github.com/TrueMordecai/sfml_mEntity/assets/60859370/6573f542-244b-4995-b699-79185a1427b2)
