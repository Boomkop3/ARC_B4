#include "Cuboid.h"

//		 G .+-------+ H
//		 .' |     .'|
//	  C +---+---+' D|
//		|   |   |   |
//		|E .+---+---+ F
//		|.'     | .'
//	  A +-------+' B

Cuboid::Cuboid() : Shape::Shape()
{
	this->set_shape_type(Shape::CUBOID);
}

Cuboid::Cuboid(double width, double height, double depth) : Shape::Shape(width, height, depth)
{
	this->set_shape_type(Shape::CUBOID);
}

void Cuboid::get_indices(std::vector<glm::vec3>& vertices_out, std::vector<glm::vec3>& indices_out) const
{
	vertices_out.resize(Cuboid::vertices_count);
	//Vertices centered
	vertices_out[A] = glm::vec3(-(this->get_width() / 2.), -(this->get_height() / 2.), this->get_depth() / 2.);		// A
	vertices_out[B] = glm::vec3(this->get_width() / 2., -(this->get_height() / 2.), this->get_depth() / 2.);			// B
	vertices_out[C] = glm::vec3(-(this->get_width() / 2.), this->get_height() / 2., this->get_depth() / 2.);			// C
	vertices_out[D] = glm::vec3(this->get_width() / 2., this->get_height() / 2., this->get_depth() / 2.);				// D
	vertices_out[E] = glm::vec3(-(this->get_width() / 2.), -(this->get_height() / 2.), -(this->get_depth() / 2.));		// E
	vertices_out[F] = glm::vec3(this->get_width() / 2., -(this->get_height() / 2.), -(this->get_depth() / 2.));		// F
	vertices_out[G] = glm::vec3(-(this->get_width() / 2.), this->get_height() / 2., -(this->get_depth() / 2.));		// G
	vertices_out[H] = glm::vec3(this->get_width() / 2., this->get_height() / 2., -(this->get_depth() / 2.));			// H

	indices_out.resize(Cuboid::indices_count);
	//CABD
	indices_out[0] = vertices_out[C];
	indices_out[1] = vertices_out[A];
	indices_out[2] = vertices_out[B];
	indices_out[3] = vertices_out[D];
	//DBFH
	indices_out[4] = vertices_out[D];
	indices_out[5] = vertices_out[B];
	indices_out[6] = vertices_out[F];
	indices_out[7] = vertices_out[H];
	//GEFH
	indices_out[8] = vertices_out[H];
	indices_out[9] = vertices_out[F];
	indices_out[10] = vertices_out[E];
	indices_out[11] = vertices_out[G];
	//GEAC 
	indices_out[12] = vertices_out[G];
	indices_out[13] = vertices_out[E];
	indices_out[14] = vertices_out[A];
	indices_out[15] = vertices_out[C];
	//EABF
	indices_out[16] = vertices_out[E];
	indices_out[17] = vertices_out[A];
	indices_out[18] = vertices_out[B];
	indices_out[19] = vertices_out[F];
	//GCDH
	indices_out[20] = vertices_out[G];
	indices_out[21] = vertices_out[C];
	indices_out[22] = vertices_out[D];
	indices_out[23] = vertices_out[H];
}



