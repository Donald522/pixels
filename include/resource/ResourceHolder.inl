#include <iostream>
#include "log/Log.h"


template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename)
{
	//std::cout << "[INFO]: Loading resource: id = " << id << ", filename = " << filename;
    _LOG_INFO( "Loading resource: id = " + std::to_string(id) + ", filename = " + filename );
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		_LOG_ERR("ResourceHolder::load - Failed to load " + filename);
		throw std::runtime_error( "ResourceHolder::load - Failed to load " + filename + "\n" );
	}

	//std::cout << "...[OK]\n";
	InsertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	//std::cout << "[INFO]: Loading resource: id = " << id << ", filename = " << filename;
    _LOG_INFO( "Loading resource: id = " + std::to_string( id ) + ", filename = " + filename );
	std::unique_ptr<Resource> resource(new Resource());
	if ( !resource->loadFromFile( filename, secondParam ) )
	{
		_LOG_ERR("ResourceHolder::load - Failed to load " + filename);
		throw std::runtime_error( "ResourceHolder::load - Failed to load " + filename + "\n" );
	}

	//std::cout << "...[OK]\n";
	InsertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

