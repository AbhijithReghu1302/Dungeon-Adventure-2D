#include "raylib.h"
#include <cmath>

const int W = 1000;
const int H = 650;

struct Enemy
{
    Vector2 pos;
    int hp;
    float attackTimer;
    bool alive;
};

float Distance(Vector2 a, Vector2 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

void StartStage(Enemy enemies[], int stage, int &enemiesInStage,
                int &defeated, Vector2 &player, int &playerHP)
{
    enemiesInStage = 4 + (stage - 1) * 2;
    defeated = 0;
    player = {200, 350};
    playerHP = 100;

    for (int i = 0; i < 8; i++)
    {
        enemies[i].alive = i < enemiesInStage;
        enemies[i].hp = 60 + (stage - 1) * 20;
        enemies[i].attackTimer = 0;

        enemies[i].pos = {
            (float)GetRandomValue(450, 900),
            (float)GetRandomValue(160, 580)
        };
    }
}

int main()
{
    InitWindow(W, H, "Dungeon Adventure - Fighting Game");
    SetTargetFPS(60);

    Vector2 player = {200, 350};
    const float speed = 220.0f;

    int playerHP = 100;
    int potions = 3;
    int defeated = 0;
    int stage = 1;
    int enemiesInStage = 4;

    float attackCooldown = 0;
    float attackEffect = 0;
    float potionMessage = 0;

    Enemy enemies[8] = {};
    StartStage(enemies, stage, enemiesInStage,
            defeated, player, playerHP);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (playerHP > 0 && defeated < enemiesInStage)
        {
            attackCooldown -= dt;
            attackEffect -= dt;
            potionMessage -= dt;

            // Player movement
            Vector2 movement = {0, 0};

            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
                movement.y -= 1;
            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
                movement.y += 1;
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
                movement.x -= 1;
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
                movement.x += 1;

            float length = sqrtf(
                movement.x * movement.x +
                movement.y * movement.y
            );

            if (length > 0)
            {
                player.x += movement.x / length * speed * dt;
                player.y += movement.y / length * speed * dt;
            }

            // Keep player inside the dungeon
            if (player.x < 25) player.x = 25;
            if (player.x > W - 25) player.x = W - 25;
            if (player.y < 125) player.y = 125;
            if (player.y > H - 25) player.y = H - 25;

            // Sword attack
            if (IsKeyPressed(KEY_SPACE) && attackCooldown <= 0)
            {
                attackCooldown = 0.4f;
                attackEffect = 0.15f;

                for (int i = 0; i < 8; i++)
                {
                    if (enemies[i].alive &&
                        Distance(player, enemies[i].pos) < 90)
                    {
                        enemies[i].hp -= 30;

                        if (enemies[i].hp <= 0)
                        {
                            enemies[i].alive = false;
                            defeated++;
                        }
                    }
                }
            }

            // Healing potion
            if (IsKeyPressed(KEY_H) && potions > 0 &&
                playerHP < 100)
            {
                playerHP += 35;
                if (playerHP > 100) playerHP = 100;

                potions--;
                potionMessage = 1.0f;
            }

            // Enemy AI
            for (int i = 0; i < 8; i++)
            {
                if (!enemies[i].alive)
                    continue;

                Vector2 diff = {
                    player.x - enemies[i].pos.x,
                    player.y - enemies[i].pos.y
                };

                float distance = Distance(player, enemies[i].pos);

                if (distance > 42)
                {
                    enemies[i].pos.x +=
                        diff.x / distance * 85.0f * dt;
                    enemies[i].pos.y +=
                        diff.y / distance * 85.0f * dt;
                }
                else
                {
                    enemies[i].attackTimer -= dt;

                    if (enemies[i].attackTimer <= 0)
                    {
                        playerHP -= 10;
                        if (playerHP < 0) playerHP = 0;

                        enemies[i].attackTimer = 1.0f;
                    }
                }
            }
        }

        // Draw game
        BeginDrawing();
        ClearBackground(Color{25, 27, 35, 255});

        // Dungeon floor
        for (int x = 0; x < W; x += 50)
            for (int y = 120; y < H; y += 50)
                DrawRectangleLines(x, y, 50, 50,
                                   Color{55, 60, 72, 255});

        // HUD
        DrawText("DUNGEON ADVENTURE", 20, 15, 28, GOLD);
        DrawText("WASD/ARROWS: Move   SPACE: Attack   H: Heal",
                 20, 55, 18, RAYWHITE);

        DrawText("PLAYER HP", 20, 88, 16, RAYWHITE);
        DrawRectangle(125, 88, 200, 18, DARKGRAY);
        DrawRectangle(125, 88, playerHP * 2, 18,
                      playerHP > 30 ? GREEN : RED);

        DrawText(TextFormat("%d / 100", playerHP),
                 335, 88, 16, RAYWHITE);

        DrawText(TextFormat("Potions: %d", potions),
                 440, 88, 18, SKYBLUE);
        DrawText(TextFormat("Stage: %d  Defeated: %d / %d",
                stage, defeated, enemiesInStage),
                600, 88, 18, GOLD);

        // Enemies
        for (int i = 0; i < 8; i++)
        {
            if (!enemies[i].alive)
                continue;

            Vector2 e = enemies[i].pos;

            DrawCircleV(e, 20, MAROON);
            DrawCircleV(e, 8, RED);

            DrawRectangle((int)e.x - 22, (int)e.y - 32,
                          44, 6, DARKGRAY);
            DrawRectangle((int)e.x - 22, (int)e.y - 32,
                          enemies[i].hp * 44 / 60, 6, GREEN);
            DrawText("ENEMY", (int)e.x - 24,
                     (int)e.y + 24, 12, RAYWHITE);
        }

        // Player
        DrawCircleV(player, 21, BLUE);
        DrawCircleV(player, 9, SKYBLUE);
        DrawText("HERO", (int)player.x - 20,
                 (int)player.y + 25, 14, RAYWHITE);

        // Sword attack effect
        if (attackEffect > 0 && playerHP > 0)
        {
            DrawCircleLines((int)player.x, (int)player.y,
                            70, GOLD);
        }

        if (potionMessage > 0)
            DrawText("+ HEALED!", (int)player.x - 35,
                     (int)player.y - 45, 18, GREEN);

        // End screens
        if (playerHP <= 0)
        {
            DrawRectangle(250, 260, 500, 120, BLACK);
            DrawText("GAME OVER", 370, 285, 40, RED);
            DrawText("Close and restart to try again",
                    345, 335, 18, RAYWHITE);
        }
        else if (defeated == enemiesInStage)
        {
            DrawRectangle(250, 260, 500, 140, BLACK);
            DrawText("DUNGEON CLEARED!", 305, 280, 34, GOLD);

            if (stage < 3)
            {
                DrawText("Press ENTER for next stage",
                        335, 335, 20, GREEN);

                if (IsKeyPressed(KEY_ENTER))
                {
                    stage++;
                    StartStage(enemies, stage, enemiesInStage,
                            defeated, player, playerHP);
                }
            }
            else
            {
                DrawText("YOU COMPLETED ALL STAGES!",
                        290, 335, 22, GREEN);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
