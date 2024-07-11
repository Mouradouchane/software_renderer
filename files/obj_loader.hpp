// OBJ_Loader.h - A Single Header OBJ Model Loader

#pragma once

#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

// Iostream - STD I/O Library
#include <iostream>

// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Library
#include <math.h>

// Print progress to console while loading (large models)
#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//	is needed and used for the OBJ Model Loader
namespace objl
{
	// Structure: Vector2
	//
	// Description: A 2D Vector that Holds Positional Data
	struct vec2d{

		// Positional Variables
		float x;
		float y;

		// Default Constructor
		vec2d()
		{
			x = 0.0f;
			y = 0.0f;
		}
		// Variable Set Constructor
		vec2d(float X_, float Y_)
		{
			x = X_;
			y = Y_;
		}
		// Bool Equals Operator Overload
		bool operator==(const vec2d& other) const
		{
			return (this->x == other.x && this->y == other.y);
		}
		// Bool Not Equals Operator Overload
		bool operator!=(const vec2d& other) const
		{
			return !(this->x == other.x && this->y == other.y);
		}
		// Addition Operator Overload
		vec2d operator+(const vec2d& right) const
		{
			return vec2d(this->x + right.x, this->y + right.y);
		}
		// Subtraction Operator Overload
		vec2d operator-(const vec2d& right) const
		{
			return vec2d(this->x - right.x, this->y - right.y);
		}
		// Float Multiplication Operator Overload
		vec2d operator*(const float& other) const
		{
			return vec2d(this->x *other, this->y * other);
		}

	};

	// Structure: Vector3
	//
	// Description: A 3D Vector that Holds Positional Data
	struct vec3d {

		// Positional Variables
		float x;
		float y;
		float z;

		// Default Constructor
		vec3d()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		// Variable Set Constructor
		vec3d(float X_, float Y_, float Z_)
		{
			x = X_;
			y = Y_;
			z = Z_;
		}
		// Bool Equals Operator Overload
		bool operator==(const vec3d& other) const
		{
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		}
		// Bool Not Equals Operator Overload
		bool operator!=(const vec3d& other) const
		{
			return !(this->x == other.x && this->y == other.y && this->z == other.z);
		}
		// Addition Operator Overload
		vec3d operator+(const vec3d& right) const
		{
			return vec3d(this->x + right.x, this->y + right.y, this->z + right.z);
		}
		// Subtraction Operator Overload
		vec3d operator-(const vec3d& right) const
		{
			return vec3d(this->x - right.x, this->y - right.y, this->z - right.z);
		}
		// Float Multiplication Operator Overload
		vec3d operator*(const float& other) const
		{
			return vec3d(this->x * other, this->y * other, this->z * other);
		}
		// Float Division Operator Overload
		vec3d operator/(const float& other) const
		{
			return vec3d(this->x / other, this->y / other, this->z / other);
		}


	};

	// Structure: Vertex
	//
	// Description: Model Vertex object that holds
	// a Position, Normal, and Texture Coordinate
	struct vertex{

		// Position Vector "V"
		vec3d position;

		// Normal Vector "VN"
		vec3d normal;

		// Texture Coordinate Vector "VT"
		vec2d texture_coordinate;
	};

	struct material{

		material() {
			name;
			Ns = 0.0f;
			Ni = 0.0f;
			d  = 0.0f;
			illum = 0;
		}

		// Material Name
		std::string name;
		// Ambient Color
		vec3d Ka;
		// Diffuse Color
		vec3d Kd;
		// Specular Color
		vec3d Ks;
		// Specular Exponent
		float Ns;
		// Optical Density
		float Ni;
		// Dissolve
		float d;
		// Illumination
		int illum;
		// Ambient Texture Map
		std::string map_Ka;
		// Diffuse Texture Map
		std::string map_Kd;
		// Specular Texture Map
		std::string map_Ks;
		// Specular Hightlight Map
		std::string map_Ns;
		// Alpha Texture Map
		std::string map_d;
		// Bump Map
		std::string map_bump;
	};

	// Structure: Mesh
	//
	// Description: A Simple Mesh Object that holds
	// a name, a vertex list, and an index list
	struct mesh {

		// Mesh Name
		std::string name;
		// Vertex List
		std::vector<vertex> vertices;
		// Index List
		std::vector<unsigned int> indices;

		// Material
		material material;

		// Default Constructor
		mesh() = default;

		// Variable Set Constructor
		mesh(std::vector<vertex>& _Vertices, std::vector<unsigned int>& _Indices){

			vertices = _Vertices;
			indices  = _Indices;
		}

	};

	// Namespace: Math
	//
	// Description: The namespace that holds all of the math
	// functions need for OBJL
	namespace math {

		// Vector3 Cross Product
		vec3d cross_vec3d(const vec3d a, const vec3d b){

			return vec3d(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
		}

		// Vector3 Magnitude Calculation
		float magnitude_vec3d(vec3d const& in)
		{
			return (sqrtf(powf(in.x, 2) + powf(in.y, 2) + powf(in.z, 2)));
		}

		// Vector3 DotProduct
		float dot_product_vec3d(const vec3d a, const vec3d b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		// Angle between 2 Vector3 Objects
		float angle_between_tow_vec3d(const vec3d a, const vec3d b)
		{
			float angle = dot_product_vec3d(a, b);
			angle /= (magnitude_vec3d(a) * magnitude_vec3d(b));
			return angle = acosf(angle);
		}

		// Projection Calculation of a onto b
		vec3d projection_vec3d(const vec3d a, const vec3d b)
		{
			vec3d  bn = b / magnitude_vec3d(b);
			return bn * dot_product_vec3d(a, bn);
		}
	}

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
	namespace algorithm {

		// Vector3 Multiplication Opertor Overload
		vec3d operator*(const float& left, const vec3d& right)
		{
			return vec3d(right.x * left, right.y * left, right.z * left);
		}

		// A test to see if P1 is on the same side as P2 of a line segment ab
		bool SameSide(vec3d p1, vec3d p2, vec3d a, vec3d b)
		{
			vec3d cp1 = math::cross_vec3d(b - a, p1 - a);
			vec3d cp2 = math::cross_vec3d(b - a, p2 - a);

			if (math::dot_product_vec3d(cp1, cp2) >= 0)
				return true;
			else
				return false;
		}

		// Generate a cross produect normal for a triangle
		vec3d GenTriNormal(vec3d t1, vec3d t2, vec3d t3)
		{
			vec3d u = t2 - t1;
			vec3d v = t3 - t1;

			vec3d normal = math::cross_vec3d(u,v);

			return normal;
		}

		// Check to see if a Vector3 Point is within a 3 Vector3 Triangle
		bool inTriangle(vec3d point, vec3d tri1, vec3d tri2, vec3d tri3)
		{
			// Test to see if it is within an infinite prism that the triangle outlines.
			bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
				&& SameSide(point, tri3, tri1, tri2);

			// If it isn't it will never be on the triangle
			if (!within_tri_prisim)
				return false;

			// Calulate Triangle's Normal
			vec3d n = GenTriNormal(tri1, tri2, tri3);

			// Project the point onto this normal
			vec3d proj = math::projection_vec3d(point, n);

			// If the distance from the triangle to the point is 0
			//	it lies on the triangle
			if (math::magnitude_vec3d(proj) == 0)
				return true;
			else
				return false;
		}

		// Split a String into a string array at a given token
		inline void split(const std::string &in,
			std::vector<std::string> &out,
			std::string token)
		{
			out.clear();

			std::string temp;

			for (int i = 0; i < int(in.size()); i++)
			{
				std::string test = in.substr(i, token.size());

				if (test == token)
				{
					if (!temp.empty())
					{
						out.push_back(temp);
						temp.clear();
						i += (int)token.size() - 1;
					}
					else
					{
						out.push_back("");
					}
				}
				else if (i + token.size() >= in.size())
				{
					temp += in.substr(i, token.size());
					out.push_back(temp);
					break;
				}
				else
				{
					temp += in[i];
				}
			}
		}

		// Get tail of string after first token and possibly following spaces
		inline std::string tail(const std::string &in)
		{
			size_t token_start = in.find_first_not_of(" \t");
			size_t space_start = in.find_first_of(" \t", token_start);
			size_t tail_start = in.find_first_not_of(" \t", space_start);
			size_t tail_end = in.find_last_not_of(" \t");
			if (tail_start != std::string::npos && tail_end != std::string::npos)
			{
				return in.substr(tail_start, tail_end - tail_start + 1);
			}
			else if (tail_start != std::string::npos)
			{
				return in.substr(tail_start);
			}
			return "";
		}

		// Get first token of string
		inline std::string firstToken(const std::string &in)
		{
			if (!in.empty())
			{
				size_t token_start = in.find_first_not_of(" \t");
				size_t token_end = in.find_first_of(" \t", token_start);
				if (token_start != std::string::npos && token_end != std::string::npos)
				{
					return in.substr(token_start, token_end - token_start);
				}
				else if (token_start != std::string::npos)
				{
					return in.substr(token_start);
				}
			}
			return "";
		}

		// Get element at given index position
		template <class T>
		inline const T & getElement(const std::vector<T> &elements, std::string &index)
		{
			int idx = std::stoi(index);
			if (idx < 0)
				idx = int(elements.size()) + idx;
			else
				idx--;
			return elements[idx];
		}
	}

	// Class: Loader
	//
	// Description: The OBJ Model Loader
	class Loader {

	public:

		// Default Constructor
		Loader() = default;

		// default destructor
		~Loader() {
			LoadedMeshes.clear();
		}

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
		bool LoadFile(std::string Path){

			try {

				// If the file is not an .obj file return false
				if (Path.substr(Path.size() - 4, 4) != ".obj") {
					return false;
				}


				std::ifstream file(Path);

				if (!file.is_open()) {
					return false;
				}

				LoadedMeshes.clear();
				LoadedVertices.clear();
				LoadedIndices.clear();

				std::vector<vec3d> Positions;
				std::vector<vec2d> TCoords;
				std::vector<vec3d> Normals;

				std::vector<vertex> vertices;
				std::vector<unsigned int> indices;

				std::vector<std::string> MeshMatNames;

				bool listening = false;
				std::string meshname;

				mesh tempMesh;

#ifdef OBJL_CONSOLE_OUTPUT
				const unsigned int outputEveryNth = 1000;
				unsigned int outputIndicator = outputEveryNth;
#endif

				std::string curline;
				while (std::getline(file, curline)) {

#ifdef OBJL_CONSOLE_OUTPUT

					if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1) {

						if (!meshname.empty()) {

							std::cout
								<< "\r- " << meshname
								<< "\t| vertices > " << Positions.size()
								<< "\t| texcoords > " << TCoords.size()
								<< "\t| normals > " << Normals.size()
								<< "\t| triangles > " << (vertices.size() / 3)
								<< (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
						}
					}

#endif

					// Generate a Mesh Object or Prepare for an object to be created
					if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g') {

						if (!listening) {

							listening = true;

							if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
							{
								meshname = algorithm::tail(curline);
							}
							else
							{
								meshname = "unnamed";
							}
						}
						else
						{
							// Generate the mesh to put into the array

							if (!indices.empty() && !vertices.empty())
							{
								// Create Mesh
								tempMesh = mesh(vertices, indices);
								tempMesh.name = meshname;

								// Insert Mesh
								LoadedMeshes.push_back(tempMesh);

								// Cleanup
								vertices.clear();
								indices.clear();
								meshname.clear();

								meshname = algorithm::tail(curline);
							}
							else
							{
								if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
								{
									meshname = algorithm::tail(curline);
								}
								else
								{
									meshname = "unnamed";
								}
							}
						}
#ifdef OBJL_CONSOLE_OUTPUT
						std::cout << std::endl;
						outputIndicator = 0;
#endif
					}
					// Generate a Vertex Position
					if (algorithm::firstToken(curline) == "v")
					{
						std::vector<std::string> spos;
						vec3d vpos;
						algorithm::split(algorithm::tail(curline), spos, " ");

						vpos.x = std::stof(spos[0]);
						vpos.y = std::stof(spos[1]);
						vpos.z = std::stof(spos[2]);

						Positions.push_back(vpos);
					}
					// Generate a Vertex Texture Coordinate
					if (algorithm::firstToken(curline) == "vt")
					{
						std::vector<std::string> stex;
						vec2d vtex;
						algorithm::split(algorithm::tail(curline), stex, " ");

						vtex.x = std::stof(stex[0]);
						vtex.y = std::stof(stex[1]);

						TCoords.push_back(vtex);
					}
					// Generate a Vertex Normal;
					if (algorithm::firstToken(curline) == "vn")
					{
						std::vector<std::string> snor;
						vec3d vnor;
						algorithm::split(algorithm::tail(curline), snor, " ");

						vnor.x = std::stof(snor[0]);
						vnor.y = std::stof(snor[1]);
						vnor.z = std::stof(snor[2]);

						Normals.push_back(vnor);
					}
					// Generate a Face (vertices & indices)
					if (algorithm::firstToken(curline) == "f")
					{
						// Generate the vertices
						std::vector<vertex> vVerts;
						GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

						// Add Vertices
						for (int i = 0; i < int(vVerts.size()); i++)
						{
							vertices.push_back(vVerts[i]);

							LoadedVertices.push_back(vVerts[i]);
						}

						std::vector<unsigned int> iIndices;

						VertexTriangluation(iIndices, vVerts);

						// Add Indices
						for (int i = 0; i < int(iIndices.size()); i++)
						{
							unsigned int indnum = (unsigned int)((vertices.size()) - vVerts.size()) + iIndices[i];
							indices.push_back(indnum);

							indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
							LoadedIndices.push_back(indnum);

						}
					}
					// Get Mesh Material Name
					if (algorithm::firstToken(curline) == "usemtl")
					{
						MeshMatNames.push_back(algorithm::tail(curline));

						// Create new Mesh, if Material changes within a group
						if (!indices.empty() && !vertices.empty())
						{
							// Create Mesh
							tempMesh = mesh(vertices, indices);
							tempMesh.name = meshname;
							int i = 2;
							while (1) {
								tempMesh.name = meshname + "_" + std::to_string(i);

								for (auto& m : LoadedMeshes)
									if (m.name == tempMesh.name)
										continue;
								break;
							}

							// Insert Mesh
							LoadedMeshes.push_back(tempMesh);

							// Cleanup
							vertices.clear();
							indices.clear();
						}

#ifdef OBJL_CONSOLE_OUTPUT
						outputIndicator = 0;
#endif
					}
					// Load Materials
					if (algorithm::firstToken(curline) == "mtllib")
					{
						// Generate LoadedMaterial

						// Generate a path to the material file
						std::vector<std::string> temp;
						algorithm::split(Path, temp, "/");

						std::string pathtomat = "";

						if (temp.size() != 1)
						{
							for (size_t i = 0; i < temp.size() - 1; i++)
							{
								pathtomat += temp[i] + "/";
							}
						}


						pathtomat += algorithm::tail(curline);

#ifdef OBJL_CONSOLE_OUTPUT
						std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
#endif

						// Load Materials
						LoadMaterials(pathtomat);
					}
				}

#ifdef OBJL_CONSOLE_OUTPUT
				std::cout << std::endl;
#endif

				// Deal with last mesh

				if (!indices.empty() && !vertices.empty())
				{
					// Create Mesh
					tempMesh = mesh(vertices, indices);
					tempMesh.name = meshname;

					// Insert Mesh
					LoadedMeshes.push_back(tempMesh);
				}

				file.close();

				// Set Materials for each Mesh
				for (size_t i = 0; i < MeshMatNames.size(); i++)
				{
					std::string matname = MeshMatNames[i];

					// Find corresponding material name in loaded materials
					// when found copy material variables into mesh material
					for (size_t j = 0; j < LoadedMaterials.size(); j++)
					{
						if (LoadedMaterials[j].name == matname)
						{
							LoadedMeshes[i].material = LoadedMaterials[j];
							break;
						}
					}
				}

				if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			catch(std::exception error){

#ifdef OBJL_CONSOLE_OUTPUT
				std::cout << "error occured while parsing obj file !\n";
#endif

				return false;
			}

		}


		// Loaded Mesh Objects
		std::vector<mesh> LoadedMeshes;
		// Loaded Vertex Objects
		std::vector<vertex> LoadedVertices;
		// Loaded Index Positions
		std::vector<unsigned int> LoadedIndices;
		// Loaded Material Objects
		std::vector<material> LoadedMaterials;

	private:
		// Generate vertices from a list of positions, 
		//	tcoords, normals and a face line
		void GenVerticesFromRawOBJ(
			std::vector<vertex>& oVerts,
			const std::vector<vec3d>& iPositions,
			const std::vector<vec2d>& iTCoords,
			const std::vector<vec3d>& iNormals,
			std::string icurline
		)
		{
			std::vector<std::string> sface, svert;
			vertex vVert;
			algorithm::split(algorithm::tail(icurline), sface, " ");

			bool noNormal = false;

			// For every given vertex do this
			for (int i = 0; i < int(sface.size()); i++)
			{
				// See What type the vertex is.
				int vtype;

				algorithm::split(sface[i], svert, "/");

				// Check for just position - v1
				if (svert.size() == 1)
				{
					// Only position
					vtype = 1;
				}

				// Check for position & texture - v1/vt1
				if (svert.size() == 2)
				{
					// Position & Texture
					vtype = 2;
				}

				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1//vn1
				if (svert.size() == 3)
				{
					if (svert[1] != "")
					{
						// Position, Texture, and Normal
						vtype = 4;
					}
					else
					{
						// Position & Normal
						vtype = 3;
					}
				}

				// Calculate and store the vertex
				switch (vtype)
				{
				case 1: // P
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.texture_coordinate = vec2d(0, 0);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 2: // P/T
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.texture_coordinate = algorithm::getElement(iTCoords, svert[1]);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 3: // P//N
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.texture_coordinate = vec2d(0, 0);
					vVert.normal = algorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				case 4: // P/T/N
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.texture_coordinate = algorithm::getElement(iTCoords, svert[1]);
					vVert.normal = algorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				default:
				{
					break;
				}
				}
			}

			// take care of missing normals
			// these may not be truly acurate but it is the 
			// best they get for not compiling a mesh with normals	
			if (noNormal)
			{
				vec3d A = oVerts[0].position - oVerts[1].position;
				vec3d B = oVerts[2].position - oVerts[1].position;

				vec3d normal = math::cross_vec3d(A, B);

				for (int i = 0; i < int(oVerts.size()); i++)
				{
					oVerts[i].normal = normal;
				}
			}
		}

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
		void VertexTriangluation(
			std::vector<unsigned int>& oIndices,
			const std::vector<vertex>& iVerts
		)
		{
			// If there are 2 or less verts,
			// no triangle can be created,
			// so exit
			if (iVerts.size() < 3)
			{
				return;
			}
			// If it is a triangle no need to calculate it
			if (iVerts.size() == 3)
			{
				oIndices.push_back(0);
				oIndices.push_back(1);
				oIndices.push_back(2);
				return;
			}

			// Create a list of vertices
			std::vector<vertex> tVerts = iVerts;

			while (true)
			{
				// For every vertex
				for (int i = 0; i < int(tVerts.size()); i++)
				{
					// pPrev = the previous vertex in the list
					vertex pPrev;
					if (i == 0)
					{
						pPrev = tVerts[tVerts.size() - 1];
					}
					else
					{
						pPrev = tVerts[i - 1];
					}

					// pCur = the current vertex;
					vertex pCur = tVerts[i];

					// pNext = the next vertex in the list
					vertex pNext;
					if (i == tVerts.size() - 1)
					{
						pNext = tVerts[0];
					}
					else
					{
						pNext = tVerts[i + 1];
					}

					// Check to see if there are only 3 verts left
					// if so this is the last triangle
					if (tVerts.size() == 3)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (iVerts[j].position == pCur.position)
								oIndices.push_back(j);
							if (iVerts[j].position == pPrev.position)
								oIndices.push_back(j);
							if (iVerts[j].position == pNext.position)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}
					if (tVerts.size() == 4)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].position == pCur.position)
								oIndices.push_back(j);
							if (iVerts[j].position == pPrev.position)
								oIndices.push_back(j);
							if (iVerts[j].position == pNext.position)
								oIndices.push_back(j);
						}

						vec3d tempVec;
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (tVerts[j].position != pCur.position
								&& tVerts[j].position != pPrev.position
								&& tVerts[j].position != pNext.position)
							{
								tempVec = tVerts[j].position;
								break;
							}
						}

						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].position == pPrev.position)
								oIndices.push_back(j);
							if (iVerts[j].position == pNext.position)
								oIndices.push_back(j);
							if (iVerts[j].position == tempVec)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}

					// If Vertex is not an interior vertex
					float angle = float(
						math::angle_between_tow_vec3d(
							pPrev.position - pCur.position, pNext.position - pCur.position
						) * (180 / 3.14159265359)
					);

					if (angle <= 0 && angle >= 180)
						continue;

					// If any vertices are within this triangle
					bool inTri = false;
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (algorithm::inTriangle(iVerts[j].position, pPrev.position, pCur.position, pNext.position)
							&& iVerts[j].position != pPrev.position
							&& iVerts[j].position != pCur.position
							&& iVerts[j].position != pNext.position)
						{
							inTri = true;
							break;
						}
					}
					if (inTri)
						continue;

					// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (iVerts[j].position == pCur.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pPrev.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pNext.position)
							oIndices.push_back(j);
					}

					// Delete pCur from the list
					for (int j = 0; j < int(tVerts.size()); j++)
					{
						if (tVerts[j].position == pCur.position)
						{
							tVerts.erase(tVerts.begin() + j);
							break;
						}
					}

					// reset i to the start
					// -1 since loop will add 1 to it
					i = -1;
				}

				// if no triangles were created
				if (oIndices.size() == 0)
					break;

				// if no more vertices
				if (tVerts.size() == 0)
					break;
			}
		}

		// Load Materials from .mtl file
		bool LoadMaterials(std::string path)
		{
			// If the file is not a material file return false
			if (path.substr(path.size() - 4, path.size()) != ".mtl")
				return false;

			std::ifstream file(path);

			// If the file is not found return false
			if (!file.is_open())
				return false;

			material tempMaterial;

			bool listening = false;

			// Go through each line looking for material variables
			std::string curline;
			while (std::getline(file, curline))
			{
				// new material and material name
				if (algorithm::firstToken(curline) == "newmtl")
				{
					if (!listening)
					{
						listening = true;

						if (curline.size() > 7)
						{
							tempMaterial.name = algorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
					else
					{
						// Generate the material

						// Push Back loaded Material
						LoadedMaterials.push_back(tempMaterial);

						// Clear Loaded Material
						tempMaterial = material();

						if (curline.size() > 7)
						{
							tempMaterial.name = algorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
				}
				// Ambient Color
				if (algorithm::firstToken(curline) == "Ka")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ka.x = std::stof(temp[0]);
					tempMaterial.Ka.y = std::stof(temp[1]);
					tempMaterial.Ka.z = std::stof(temp[2]);
				}
				// Diffuse Color
				if (algorithm::firstToken(curline) == "Kd")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Kd.x = std::stof(temp[0]);
					tempMaterial.Kd.y = std::stof(temp[1]);
					tempMaterial.Kd.z = std::stof(temp[2]);
				}
				// Specular Color
				if (algorithm::firstToken(curline) == "Ks")
				{
					std::vector<std::string> temp;
					algorithm::split(algorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ks.x = std::stof(temp[0]);
					tempMaterial.Ks.y = std::stof(temp[1]);
					tempMaterial.Ks.z = std::stof(temp[2]);
				}
				// Specular Exponent
				if (algorithm::firstToken(curline) == "Ns")
				{
					tempMaterial.Ns = std::stof(algorithm::tail(curline));
				}
				// Optical Density
				if (algorithm::firstToken(curline) == "Ni")
				{
					tempMaterial.Ni = std::stof(algorithm::tail(curline));
				}
				// Dissolve
				if (algorithm::firstToken(curline) == "d")
				{
					tempMaterial.d = std::stof(algorithm::tail(curline));
				}
				// Illumination
				if (algorithm::firstToken(curline) == "illum")
				{
					tempMaterial.illum = std::stoi(algorithm::tail(curline));
				}
				// Ambient Texture Map
				if (algorithm::firstToken(curline) == "map_Ka")
				{
					tempMaterial.map_Ka = algorithm::tail(curline);
				}
				// Diffuse Texture Map
				if (algorithm::firstToken(curline) == "map_Kd")
				{
					tempMaterial.map_Kd = algorithm::tail(curline);
				}
				// Specular Texture Map
				if (algorithm::firstToken(curline) == "map_Ks")
				{
					tempMaterial.map_Ks = algorithm::tail(curline);
				}
				// Specular Hightlight Map
				if (algorithm::firstToken(curline) == "map_Ns")
				{
					tempMaterial.map_Ns = algorithm::tail(curline);
				}
				// Alpha Texture Map
				if (algorithm::firstToken(curline) == "map_d")
				{
					tempMaterial.map_d = algorithm::tail(curline);
				}
				// Bump Map
				if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump")
				{
					tempMaterial.map_bump = algorithm::tail(curline);
				}
			}

			// Deal with last material

			// Push Back loaded Material
			LoadedMaterials.push_back(tempMaterial);

			// Test to see if anything was loaded
			// If not return false
			if (LoadedMaterials.empty())
				return false;
			// If so return true
			else
				return true;
		}
	};

}

#endif
