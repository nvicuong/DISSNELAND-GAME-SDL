#include "Enemy1.h"
#include <vector>
#include <queue>
#include <utility>



int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
int dy[] = {0, 1, 0, -1, 1, -1, -1, 1};

bool isValid(int x, int y, std::vector<std::vector<bool>>& visited) {
    if (x < 0 || x >= 20 || y < 0 || y >= 50)
        return false;
    if (Map::map1[x][y] == 1 || visited[x][y])
        return false;
    return true;
}

void bfs(int sx, int sy, int ex, int ey, std::vector<std::vector<bool>>& visited, std::vector<std::vector<int>>& dist, std::vector<std::pair<int, int>> path[20][50], std::vector<std::pair<int, int>> vec2D[20][50]) {
    std::queue<std::pair<int, int>> q;

    visited[sx][sy] = true;
    dist[sx][sy] = 0;

    std::pair<int, int> qPair(sx, sy);
    q.push(qPair);

    while (!q.empty()) {
        std::pair<int, int> node = q.front();
        q.pop();

        int x = node.first;
        int y = node.second;

        if (x == ex && y == ey) {
            return;
        }

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, visited)) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                std::pair<int, int> r(nx, ny);
                q.push(r);
                path[nx][ny] = path[x][y];
                vec2D[nx][ny] = vec2D[x][y];

                std::pair<int, int> pathPair(nx, ny);
                std::pair<int, int> vec2DPair(dy[i], dx[i]);

                path[nx][ny].push_back(pathPair);
                vec2D[nx][ny].push_back(vec2DPair);
            }
        }
    }
    for (auto p : vec2D[ex][ey]) {
        std::cout << p.first << " " << p.second <<std::endl;
    }
    // std::cout << "sx: " << sx << " sy: " << sy << std::endl
    //           << "ex: " << ex << " ey: " << ey << std::endl
    //           << "-----------------" << std::endl;
}

bool Enemy1::huntPlayerVer2(const SDL_Rect& eneRect, const SDL_Rect& recP)
{
    
    if (abs(eneRect.x - xpos) >= 48 || abs(eneRect.y - ypos) >= 48)
    {
    std::vector<std::vector<bool>> visited(20, std::vector<bool>(50));
    std::vector<std::vector<int>> dist(20, std::vector<int>(50));

    std::vector<std::pair<int, int>> path[20][50];
    std::vector<std::pair<int, int>> vec2D[20][50];

    int sx = eneRect.y / 48;
    int sy = eneRect.x / 48;

    int ex = (recP.y + (recP.h/2)) / 48;
    int ey = (recP.x + (recP.w/2)) / 48;

    bfs(sx, sy, ex, ey, visited, dist, path, vec2D);
    
    if (!vec2D[ex][ey].empty())
    {
        int x = vec2D[ex][ey].front().first;
        int y = vec2D[ex][ey].front().second;
        // std::cout << "no empty" << std::endl;
        Vector2D vel(2*x, 2*y);
        transform->velocity = vel;
        xpos = eneRect.x;
        ypos = eneRect.y;
        
        sprite->index = 1;
        sprite->Play(tag);
        return true;
    }
    else
    {
        // std::cout << "empty" << std::endl;
        Vector2D vel(0, 0);
        transform->velocity = vel;
        return false;
    }
    }
    return false;


}


std::vector<float> desX = { -1, -0.95, -0.9, -0.85, -0.8, -0.75, -0.7, -0.65, -0.6, -0.55, -0.5, -0.45, -0.4, -0.35, -0.3, -0.25, -0.2, -0.15, -0.1, -0.05, 0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1 };
std::vector<float> desY = { -1, -0.95, -0.9, -0.85, -0.8, -0.75, -0.7, -0.65, -0.6, -0.55, -0.5, -0.45, -0.4, -0.35, -0.3, -0.25, -0.2, -0.15, -0.1, -0.05, 0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1 };

float getPosDesY(float posX, float radios)
{
    float posY = sqrt((radios * radios) - (posX * posX));
    return posY;
}
Animation aniProject[] =
{
    Animation(4, 100, 10, 15),
    Animation(4, 100, 10, 15)
};
int sizeaniProject = 2;

bool flip = 0;
void Enemy1::walkAround()
{
    distance += speed;

    if (distance > 500)
    {
        if (flip)
        {
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            flip = 0;
        }
        else
        {
            sprite->spriteFlip = SDL_FLIP_NONE;
            flip = 1;
        }
        transform->velocity.x = -transform->velocity.x;
        distance = 0;
    }
}

bool Enemy1::completedAttack()
{
    //std::cout << sprite->index << std::endl;
    if ((sprite->currentFrame >= sprite->frames - 1) && sprite->index == 3)
    {
    // std::cout << "currenFrame: " << sprite->currentFrame << std::endl;
    // std::cout << "frames: " << sprite->frames << std::endl;
        //std::cout << "..";
        attacked = 1;
        return true;
    }
    return false;
}


Vector2D Enemy1::getVel(const SDL_Rect& eneRect, const SDL_Rect& recP)
{
    float posX = transform->position.x;
    float posY = transform->position.y;

    float radios = 1;
    float gDesX = posX + (-1) * 200;
    float gDesY = posY + (-1) * 200;

    float idX = 0;
    float idY = 0;

    //viet phuong trinh duong thang
    float a = std::pow(recP.x + recP.w / 2 - gDesX, 2) + std::pow(recP.y + recP.h / 2 - gDesY, 2);
    for (auto i : desX)
    {
        for (auto j : desY)
        {
            gDesX = posX + i * 200;
            gDesY = posY + j * 200;
            float b = std::pow(recP.x + recP.w / 2 - gDesX, 2) + std::pow(recP.y + recP.h / 2 - gDesY, 2);
            if (a > (std::min(a, b)))
            {
                a = b;
                idX = i;
                idY = j;

            }
        }
    }

    while (idX * idX + idY * idY < 1 && !(idX == 0 && idY == 0) && (idX != 0 || idY != 0))
    {
        idX *= 2;
        idY *= 2;
    }
    //std::cout << "idX: " << idX << " idY: " << idY << std::endl;
    return Vector2D(idX, idY);
}

void Enemy1::fireGun(const SDL_Rect& eneRect, const SDL_Rect& recP, AssetManager* assets)
{
    if (Collision::findAABB(eneRect, recP))
    {
        float posX = transform->position.x;
        float posY = transform->position.y;
        Vector2D getV = Enemy1::getVel(eneRect, recP);
        assets->CreateProJectile(Vector2D(posX, posY), getV, 10, 10, 200, 2, "projectile", 0, aniProject, sizeaniProject);

    }
}

void Enemy1::attackPlayer(const SDL_Rect& eneRect, const SDL_Rect& recP)
{
    if (timer < 5)
    {
        //std::cout << sprite->currentFrame << std::endl;
        if (eneRect.x % 48 == 0 && eneRect.y % 48 == 0)
        {
        transform->velocity = Vector2D(0, 0);
        }
        bool a;
        a = completedAttack();
        if (Collision::AABB(eneRect, recP) && a)
        {
            //std::cout << "xx" << std::endl;
            hit = 1;
        }
        sprite->index = 3;
        //std::cout << "attacked: " << attacked << std::endl;
        if (attacked)
        {
            sprite->index = 0;
            //unAttack = 1;
        }
        //std::cout << sprite->index << std::endl;
        sprite->Play(tag);

    }
    else
    {
    if (transform->velocity.x != 0 || transform->velocity.y != 0)
    {
        sprite->index = 1;
    }
    else
    {
        sprite->index = 0;
    }
        attacked = 0;
        //std::cout << "xx";
        Enemy1::huntPlayerVer2(eneRect, recP);
        
        if (transform->velocity.x > 0)
        {
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
        else
        {
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        }
        if (Collision::AABB(eneRect, recP))
        {
            timer = 0;
            sprite->currentFrame = 0;
        }
        else
        {
            sprite->Play(tag);
        }
    }
    
}

void Enemy1::getHurt()
{
    sprite->index = 2;
    transform->velocity = Vector2D(0, 0);
    sprite->Play(tag);
}
