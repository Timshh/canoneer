#include "assetManager.h"

AssetManager::AssetManager() : Font(FontPath) {}

sf::Font* AssetManager::GetFont() { return &Font; }