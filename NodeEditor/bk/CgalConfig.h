//
// Created by Q on 24-4-16.
//

#pragma once
#include <memory>
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Simple_cartesian.h"
#include "CGAL/Filtered_kernel.h"
#include "CGAL/Polygon_2.h"
#include "CGAL/Polygon_with_holes_2.h"
#include "CGAL/create_offset_polygons_2.h"
#include "CGAL/create_straight_skeleton_from_polygon_with_holes_2.h"
#include "CGAL/create_offset_polygons_from_polygon_with_holes_2.h"
#include "boost/shared_ptr.hpp"
#include "CGAL/Cartesian.h"
#include <CGAL/Polyline_simplification_2/simplify.h>
#include <CGAL/Polyline_simplification_2/Squared_distance_cost.h>
#include <CGAL/Polyline_simplification_2/Scaled_squared_distance_cost.h>
#include <CGAL/Polyline_simplification_2/Hybrid_squared_distance_cost.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Filtered_kernel<Epeck> K;
//typedef CGAL::Simple_cartesian<double> K;

typedef K::Point_2 Point_2;
typedef std::shared_ptr<Point_2> Point_2Ptr;
//typedef KSimple::Point_2 Point_2Simple;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef std::vector<Polygon_2> Polygons;
typedef CGAL::Polygon_with_holes_2<K> PWH;
typedef boost::shared_ptr<PWH> PWHPtr;
typedef std::vector<PWHPtr> PWHPtrVector;
typedef CGAL::Straight_skeleton_2<K> Ss ;
typedef boost::shared_ptr<Polygon_2> PolygonPtr ;
typedef boost::shared_ptr<Ss> SsPtr ;
typedef std::vector<PolygonPtr> PolygonPtrVector ;
typedef CGAL::Segment_2<K> Segment_2;
typedef std::shared_ptr<Segment_2> Segment_2Ptr;
typedef std::vector<Segment_2Ptr> Segment_2Vector;
//typedef CGAL::Segment_2<KSimple> Segment_2Simple;
typedef CGAL::Line_2<K> Line_2;
typedef CGAL::Polyline_simplification_2::Stop_above_cost_threshold Stop;
typedef CGAL::Polyline_simplification_2::Squared_distance_cost Cost;

