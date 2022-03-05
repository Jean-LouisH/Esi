// MIT License
// 
// Copyright (c) 2020 Jean-Louis Haywood
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "asset_cache.hpp"

Omnia::AssetCache* Omnia::AssetCache::instance = nullptr;

void Omnia::AssetCache::store(std::shared_ptr<Omnia::Asset> asset)
{
	AssetCache* instance = getInstance();

	if (!instance->assets.count(asset->getName()))
		instance->assets.emplace(asset->getName(), asset);
}

void Omnia::AssetCache::deleteAsset(std::string filepath)
{
	getInstance()->assets.erase(filepath);
}

void Omnia::AssetCache::deleteAllAssets()
{
	getInstance()->assets.clear();
}

std::unordered_map<std::string, std::shared_ptr<Omnia::Asset>> Omnia::AssetCache::getAssets()
{
	return getInstance()->assets;
}

Omnia::AssetCache* Omnia::AssetCache::getInstance()
{
	if (instance == nullptr)
		instance = new AssetCache();
	return instance;
}