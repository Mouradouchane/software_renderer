
#pragma once

#ifndef OBJ_LOADER_CPP
#define OBJ_LOADER_CPP

#define TINYOBJLOADER_IMPLEMENTATION 
#include "loader.hpp"
#include "tiny_obj_loader.h"

static const char* loader_error_title = "obj loader error";
static const char* loader_warn_title  = "obj loader warning";

int8_t loader::load_models() {

	// allocate pointer for meshes
	g_meshes  = new std::vector<mesh*>(g_obj_files_list.size());
	g_pmeshes = new std::vector<mesh*>(g_obj_files_list.size());

	// try to load meshes
	uint32_t m = 0;
	for (const std::string& file_name : g_obj_files_list) {
		
		mesh* model = new mesh();
	
		if (loader::load_obj_file(file_name, model) == OPEN_OBJ_FAILED) {
			return OPEN_OBJ_FAILED;
		}

		(*g_meshes)[m] = model;
		m += 1;

	}

	return OPEN_OBJ_SUCCESS;
}

int8_t loader::load_obj_file(
	std::string const& file_name, mesh* destination
){

	if (destination == nullptr) return MESH_DESTINIATION_NULLPTR;

	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = g_models_path; // Path to material files

	tinyobj::ObjReader reader;

	// open and parse obj files process

	if (!reader.ParseFromFile(file_name, reader_config)) {

		if (!reader.Error().empty()) {

			show_error(loader_error_title, "failed to open obj file : " + *(file_name.c_str()));
		}

		return OPEN_OBJ_FAILED;
	}

	if (!reader.Warning().empty()) {
		show_warn(loader_warn_title, reader.Warning());
	}

	/*
		here is the process of making our type of meshses
		from tiny_obj_loader library
	*/

	auto& attrib = reader.GetAttrib(); // contains : vertices , normals , uvs 
	auto& shapes = reader.GetShapes(); // contains meshes faces indexces
	auto& materials = reader.GetMaterials();

	/* 
	 // note: just i disabled this warn messagebox temporary !
	if (shapes.size() > 1) {
		show_warn(loader_warn_title, "obj file with multiple meshes is not supported");
	}
	*/

	destination->name = shapes[0].name;

	// allocate memory for mesh data
	destination->vertices = std::vector<vec3d>( size_t(attrib.vertices.size() / 3) );
	destination->normals  = std::vector<vec3d>( size_t(attrib.normals.size()  / 3) );
	destination->texture_coordinates = std::vector<vec_uv>( size_t(attrib.texcoords.size() / 2) );
	destination->indeces = std::vector<indexces>(shapes[0].mesh.indices.size());

	// todo: multi-threaded copying
	// copying vertices to model
	for (size_t v = 0 , V = 0; v < (attrib.vertices.size() - 3) && V < destination->vertices.size() ; v += 3 , V += 1) {

		destination->vertices[V] = vec3d{
			attrib.vertices[v],
			attrib.vertices[v+1],
			attrib.vertices[v+2],
		};

	}

	// todo: multi-threaded copying
	// copying normals to model
	for (size_t n = 0 , N = 0; n < (attrib.normals.size() - 3) && N < destination->normals.size(); n += 3 , N += 1) {

		destination->normals[N] = vec3d{
			attrib.normals[n],
			attrib.normals[n + 1],
			attrib.normals[n + 2],
		};

	}

	// todo: multi-threaded copying
	// copying textuer-coordinates
	for (size_t t = 0 , T = 0; t < (attrib.texcoords.size() - 2) && T < destination->texture_coordinates.size(); t += 2 , T += 1) {

		destination->texture_coordinates[T] = vec_uv{
			attrib.texcoords[t],
			attrib.texcoords[t + 1]
		};

	}

	// todo: multi-threaded copying
	// copying indeces
	for (size_t s = 0; s < shapes[0].mesh.indices.size(); s++) {

		destination->indeces[s] = indexces{
			shapes[0].mesh.indices[s].vertex_index,
			shapes[0].mesh.indices[s].texcoord_index,
			shapes[0].mesh.indices[s].normal_index,
		};

	}
	
	destination = destination;
	return OPEN_OBJ_SUCCESS;
}


#endif
