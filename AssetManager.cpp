#include "AssetManager.h"
#include "Components.h"
#include <algorithm>
AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateProJectile(Vector2D pos, Vector2D vel, int width, int height, int range, int speed, std::string id, int index, Animation idArray[], int sizeidArray)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, width, height, 1);
	projectile.addComponent<SpriteComponent>(id, idArray, sizeidArray);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::CreateEnemy1(Vector2D pos,int width, int height, std::string id, Animation idArray[], int sizeidArray)
{
	auto& collider(manager->addEntity());
	collider.addComponent<TransformComponent>(pos.x, pos.y, width, height, 1);
	collider.addComponent<SpriteComponent>(id, idArray, sizeidArray);
	collider.addComponent<Enemy1>(10, "enemy1");
	collider.addComponent<StatusBar>(100, 100, width);
	collider.addComponent<ColliderComponent>("enemy1");
	collider.addGroup(Game::groupEnemy);
}

void AssetManager::CreateEnemy2(Vector2D pos, int width, int height, std::string id, Animation idArray[], int sizeidArray)
{
	auto& collider(manager->addEntity());
	collider.addComponent<TransformComponent>(pos.x, pos.y, width, height, 1);
	collider.addComponent<SpriteComponent>(id, idArray, sizeidArray);
	collider.addComponent<ColliderComponent>("enemy2");
	collider.addComponent<Enemy1>(10, "enemy2");
	collider.addComponent<StatusBar>(100, 100, width);
	collider.addGroup(Game::groupEnemy);
}

void AssetManager::AddVector(std::string id)
{
	std::vector< SDL_Texture*> animationEntity;
	textures.emplace(id, animationEntity);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	auto it = std::find(textures[id].begin(), textures[id].end(), TextureManager::LoadTexture(path));
	if (it == textures[id].end())
	{
		//std::cout << "them";
		textures[id].push_back(TextureManager::LoadTexture(path));
	}
}

SDL_Texture* AssetManager::GetTexture(std::string id, int index)
{
	//std::cout << id;
	if (index >= textures[id].size()) {
		std::cout << "Index out of range";
		throw std::out_of_range("Index out of range!");
	}
	return textures[id].at(index);
}