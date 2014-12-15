/*****************************************************************************
* Copyright (c) 2014, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory. 
* 
* All rights reserved.
* 
* This source code cannot be distributed without further review from 
* Lawrence Livermore National Laboratory.
*****************************************************************************/

///
/// file: Node.h
///

#ifndef __CONDUIT_NODE_H
#define __CONDUIT_NODE_H

// -- conduit lib includes -- 

#include "Core.h"
#include "Error.h"
#include "Endianness.h"
#include "DataType.h"
#include "DataArray.h"
#include "Schema.h"
#include "Generator.h"
#include "NodeIterator.h"

// -- stl includes -- 
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


namespace conduit
{
    
class Generator;
class NodeIterator;

/// For each dtype, the Node class provides:
///  constructor: explicit Node({DTYPE}  data);
///  assign op:  Node &operator=({DTYPE} data);
///  setters: 
///      void set({DTYPE} data);
///      void set_path({DTYPE} data);
///  external setters: 
///      void set_external({DTYPE} *data,...);
///      void set_path_external({DTYPE} *data,...);
///  accessor: {DTYPE} as_{DTYPE};

class CONDUIT_API Node
{
public:
    friend class Generator;
    friend class NodeIterator;

    /// @name Constructors
    ///@{

    Node(); // empty node
    Node(const Node &node);

    explicit Node(const DataType &dtype);
    explicit Node(const Generator &gen);
    explicit Node(const Schema &schema);
        
    // convience interface:
    Node(const std::string &json_schema, void *data);
    Node(const Schema &schema, void *data);
    Node(const DataType &dtype, void *data);
    Node(const Schema &schema, const std::string &stream_path, bool mmap=false);

    
    explicit Node(int8   data);
    explicit Node(int16  data);
    explicit Node(int32  data);
    explicit Node(int64  data);

    explicit Node(uint8   data);
    explicit Node(uint16  data);
    explicit Node(uint32  data);
    explicit Node(uint64  data);

    explicit Node(float32 data);
    explicit Node(float64 data);

    explicit Node(const std::vector<int8>   &data);
    explicit Node(const std::vector<int16>  &data);    
    explicit Node(const std::vector<int32>  &data);
    explicit Node(const std::vector<int64>  &data);

    explicit Node(const std::vector<uint8>   &data);
    explicit Node(const std::vector<uint16>  &data);    
    explicit Node(const std::vector<uint32>  &data);
    explicit Node(const std::vector<uint64>  &data);
    
    explicit Node(const std::vector<float32>  &data);
    explicit Node(const std::vector<float64>  &data);

    explicit Node(const bool8_array  &data);    

    explicit Node(const int8_array  &data);
    explicit Node(const int16_array &data);
    explicit Node(const int32_array &data);
    explicit Node(const int64_array &data);

    explicit Node(const uint8_array  &data);
    explicit Node(const uint16_array &data);
    explicit Node(const uint32_array &data);
    explicit Node(const uint64_array &data);

    explicit Node(const float32_array &data);
    explicit Node(const float64_array &data);
    
    explicit Node(const std::string  &data);

   ///@}

    ~Node();

    void reset();

    // -- begin alt construction -- 
    /// @name Alternate Construction
    ///
    ///@{

    void generate(const Generator &gen);    

    void generate(const std::string &json_schema,
                  void *data);

    void generate(const std::string &json_schema,
                  const std::string &protocol,
                  void *data = NULL);
    
    void load(const Schema &schema,
              const std::string &stream_path);

    /// dual file (schema + data) load
    void load(const std::string &ibase);

    void mmap(const Schema &schema,
              const std::string &stream_path);

    /// dual file (schema + data) mmap load
    void mmap(const std::string &ibase); 
    
    // -- end alt construction -- 
    ///@}
    
    // -- begin setters (general) -- 
    /// @name Node Setters
    ///
    ///@{

    // -- begin set --  
    /// @name Standard Node::set(...) methods
    /// set(...) methods follow copy semantics. 
    ///@{
    
    void set(const Node &data);
    void set(const DataType &dtype);

    void set(const Schema &schema);

//    void set(const Schema &schema, void *data);
    void set(const DataType &dtype, void *data);

    //
    // Note: when bool8 maps to a bool, any pointer type will
    // implicilty convert to bool. To avoid confusion, we 
    // have an explicit set_bool8, instead of set(bool8 val)
    //
    void set_bool8(bool8 data);

    void set(int8 data);
    void set(int16 data);
    void set(int32 data);
    void set(int64 data);

    void set(uint8 data);
    void set(uint16 data);
    void set(uint32 data);
    void set(uint64 data);

    void set(float32 data);
    void set(float64 data);


    void set(const std::vector<int8>   &data);
    void set(const std::vector<int16>  &data);
    void set(const std::vector<int32>  &data);
    void set(const std::vector<int64>  &data);

    void set(const std::vector<uint8>   &data);
    void set(const std::vector<uint16>  &data);
    void set(const std::vector<uint32>  &data);
    void set(const std::vector<uint64>  &data);

    void set(const std::vector<float32> &data);
    void set(const std::vector<float64> &data);

    void set(const bool8_array  &data);

    void set(const int8_array  &data);
    void set(const int16_array &data);
    void set(const int32_array &data);
    void set(const int64_array &data);

    void set(const uint8_array  &data);
    void set(const uint16_array &data);
    void set(const uint32_array &data);
    void set(const uint64_array &data);

    void set(const float32_array &data);
    void set(const float64_array &data);

    // bytestr use cases:
    void set(const char* data, index_t dtype_id = DataType::CHAR8_STR_T);
    void set(const std::string &data);
    
    // set pointer cases, these use the set array cases above
    void set(bool8 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::bool8),
             index_t element_bytes = sizeof(conduit::bool8),
             index_t endianness = Endianness::DEFAULT_T);

    void set(int8  *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int8),
             index_t element_bytes = sizeof(conduit::int8),
             index_t endianness = Endianness::DEFAULT_T);
    
    void set(int16 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int16),
             index_t element_bytes = sizeof(conduit::int16),
             index_t endianness = Endianness::DEFAULT_T);
    
    void set(int32 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int32),
             index_t element_bytes = sizeof(conduit::int32),
             index_t endianness = Endianness::DEFAULT_T);

    void set(int64 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::int64),
             index_t element_bytes = sizeof(conduit::int64),
             index_t endianness = Endianness::DEFAULT_T);

    void set(uint8  *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint8),
             index_t element_bytes = sizeof(conduit::uint8),
             index_t endianness = Endianness::DEFAULT_T);

    void set(uint16 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint16),
             index_t element_bytes = sizeof(conduit::uint16),
             index_t endianness = Endianness::DEFAULT_T);

    void set(uint32 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint32),
             index_t element_bytes = sizeof(conduit::uint32),
             index_t endianness = Endianness::DEFAULT_T);
                      
    void set(uint64 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::uint64),
             index_t element_bytes = sizeof(conduit::uint64),
             index_t endianness = Endianness::DEFAULT_T);

    void set(float32 *data,
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::float32),
             index_t element_bytes = sizeof(conduit::float32),
             index_t endianness = Endianness::DEFAULT_T);

    void set(float64 *data, 
             index_t num_elements = 1,
             index_t offset = 0,
             index_t stride = sizeof(conduit::float64),
             index_t element_bytes = sizeof(conduit::float64),
             index_t endianness = Endianness::DEFAULT_T);

    ///@}    
    // -- end set --

    // -- begin set_path --
    /// @name Path based Node::set(...) methods
    /// set_path(...) methods follow copy semantics, 
    /// and allow you to use an explciit path for the destination node.
    ///@{
             
     void set_path(const std::string &path,const Node& data) 
         {fetch(path).set(data);}

     void set_path(const std::string &path,const DataType& dtype)
         {fetch(path).set(dtype);}

     void set_path(const std::string &path,const Schema &schema)
         {fetch(path).set(schema);}
              
     void set_path(const std::string &path,const Schema &schema, void* data)
         {fetch(path).set(schema,data);}
     void set_path(const std::string &path,const DataType &dtype, void* data)
         {fetch(path).set(dtype,data);}
         
     void set_path(const std::string &path,bool8 data)
         {fetch(path).set(data);}         

     void set_path(const std::string &path,int8 data)
         {fetch(path).set(data);}

     void set_path(const std::string &path,int16 data)
         {fetch(path).set(data);}
         
     void set_path(const std::string &path,int32 data)
         {fetch(path).set(data);}
     void set_path(const std::string &path,int64 data)
         {fetch(path).set(data);}
 
     void set_path(const std::string &path,uint8 data)
         {fetch(path).set(data);}
         
     void set_path(const std::string &path,uint16 data)
         {fetch(path).set(data);}
     void set_path(const std::string &path,uint32 data)
         {fetch(path).set(data);}
     void set_path(const std::string &path,uint64 data)
         {fetch(path).set(data);}

     void set_path(const std::string &path,float32 data)
         {fetch(path).set(data);}
     void set_path(const std::string &path,float64 data)
         {fetch(path).set(data);}

     void set_path(const std::string &path,const std::vector<int8>   &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<int16>  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<int32>  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<int64>  &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const std::vector<uint8>   &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<uint16>  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<uint32>  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<uint64>  &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const std::vector<float32> &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const std::vector<float64> &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const bool8_array  &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const int8_array  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const int16_array &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const int32_array &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const int64_array &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const uint8_array  &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const uint16_array &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const uint32_array &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const uint64_array &data)
        {fetch(path).set(data);}

     void set_path(const std::string &path,const float32_array &data)
        {fetch(path).set(data);}
     void set_path(const std::string &path,const float64_array &data)
        {fetch(path).set(data);}

     // bytestr use cases:
     void set_path(const std::string &path,
                   const char* data, 
                   index_t dtype_id = DataType::CHAR8_STR_T)
        {fetch(path).set(data,dtype_id);}

     void set_path(const std::string &path,
                   const std::string &data)
        {fetch(path).set(data);}
        
     // set pointer cases, these use the set array cases above
     void set_path(const std::string &path,
                   bool8 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::bool8),
                   index_t element_bytes = sizeof(conduit::bool8),
                   index_t endianness = Endianness::DEFAULT_T)
        {fetch(path).set(data,
                         num_elements,
                         offset,
                         stride,
                         element_bytes,
                         endianness);}
        
     void set_path(const std::string &path,int8  *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::int8),
                   index_t element_bytes = sizeof(conduit::int8),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}
        
     void set_path(const std::string &path,
                   int16 *data, 
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::int16),
                   index_t element_bytes = sizeof(conduit::int16),
                   index_t endianness = Endianness::DEFAULT_T)
        {fetch(path).set(data,
                         num_elements,
                         offset,
                         stride,
                         element_bytes,
                         endianness);}

     void set_path(const std::string &path,
                   int32 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::int32),
                   index_t element_bytes = sizeof(conduit::int32),
                   index_t endianness = Endianness::DEFAULT_T)
        {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}

     void set_path(const std::string &path,
                   int64 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::int64),
                   index_t element_bytes = sizeof(conduit::int64),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}

     void set_path(const std::string &path,
                   uint8  *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::uint8),
                   index_t element_bytes = sizeof(conduit::uint8),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}

     void set_path(const std::string &path,
                   uint16 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::uint16),
                   index_t element_bytes = sizeof(conduit::uint16),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}

     void set_path(const std::string &path,
                   uint32 *data, 
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::uint32),
                   index_t element_bytes = sizeof(conduit::uint32),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}
              
     void set_path(const std::string &path,
                   uint64 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::uint64),
                   index_t element_bytes = sizeof(conduit::uint64),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}

     void set_path(const std::string &path,
                   float32 *data,
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::float32),
                   index_t element_bytes = sizeof(conduit::float32),
                   index_t endianness = Endianness::DEFAULT_T)
           {fetch(path).set(data,
                            num_elements,
                            offset,
                            stride,
                            element_bytes,
                            endianness);}

     void set_path(const std::string &path,
                   float64 *data, 
                   index_t num_elements = 1,
                   index_t offset = 0,
                   index_t stride = sizeof(conduit::float64),
                   index_t element_bytes = sizeof(conduit::float64),
                   index_t endianness = Endianness::DEFAULT_T)
       {fetch(path).set(data,
                        num_elements,
                        offset,
                        stride,
                        element_bytes,
                        endianness);}
    ///@}
    // -- end set_path --
                        
    // -- begin set_external --
    /// @name Node::set_external(...) methods
    /// set_external(...) methods allow the node to point to external memory.
    ///@{
    void set_external(bool8 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::bool8),
                      index_t element_bytes = sizeof(conduit::bool8),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(int8  *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int8),
                      index_t element_bytes = sizeof(conduit::int8),
                      index_t endianness = Endianness::DEFAULT_T);
    
    void set_external(int16 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int16),
                      index_t element_bytes = sizeof(conduit::int16),
                      index_t endianness = Endianness::DEFAULT_T);
    
    void set_external(int32 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int32),
                      index_t element_bytes = sizeof(conduit::int32),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(int64 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::int64),
                      index_t element_bytes = sizeof(conduit::int64),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(uint8  *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint8),
                      index_t element_bytes = sizeof(conduit::uint8),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(uint16 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint16),
                      index_t element_bytes = sizeof(conduit::uint16),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(uint32 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint32),
                      index_t element_bytes = sizeof(conduit::uint32),
                      index_t endianness = Endianness::DEFAULT_T);
                      
    void set_external(uint64 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint64),
                      index_t element_bytes = sizeof(conduit::uint64),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(float32 *data,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::float32),
                      index_t element_bytes = sizeof(conduit::float32),
                      index_t endianness = Endianness::DEFAULT_T);

    void set_external(float64 *data, 
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::float64),
                      index_t element_bytes = sizeof(conduit::float64),
                      index_t endianness = Endianness::DEFAULT_T);

    
    void set_external(std::vector<int8>   &data);
    void set_external(std::vector<int16>  &data);
    void set_external(std::vector<int32>  &data);
    void set_external(std::vector<int64>  &data);

    void set_external(std::vector<uint8>   &data);
    void set_external(std::vector<uint16>  &data);
    void set_external(std::vector<uint32>  &data);
    void set_external(std::vector<uint64>  &data);

    void set_external(std::vector<float32> &data);
    void set_external(std::vector<float64> &data);

    void set_external(const bool8_array  &data);

    void set_external(const int8_array  &data);
    void set_external(const int16_array &data);
    void set_external(const int32_array &data);
    void set_external(const int64_array &data);

    void set_external(const uint8_array  &data);
    void set_external(const uint16_array &data);
    void set_external(const uint32_array &data);
    void set_external(const uint64_array &data);

    void set_external(const float32_array &data);
    void set_external(const float64_array &data);

    // bytestr use cases:
    void set_external(char *data, 
                      index_t dtype_id,
                      index_t num_elements = 1,
                      index_t offset = 0,
                      index_t stride = sizeof(conduit::uint8),
                      index_t element_bytes = sizeof(conduit::uint8),
                      index_t endianness = Endianness::DEFAULT_T);
    ///@}
    // -- end set_external --

    // -- begin set_path_external --
    /// @name Node::set_path_external(...) methods
    /// set_path_external(...) methods allow the node to point to external memory, 
    /// and allow you to use an explciit path for the destination node.
    ///@{

    void set_path_external(const std::string &path,
                           bool8 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::bool8),
                           index_t element_bytes = sizeof(conduit::bool8),
                           index_t endianness = Endianness::DEFAULT_T)
                         {fetch(path).set_external(data,
                                                   num_elements,
                                                   offset,
                                                   stride,
                                                   element_bytes,
                                                   endianness);
                         }

    void set_path_external(const std::string &path,
                           int8  *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int8),
                           index_t element_bytes = sizeof(conduit::int8),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           int16 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int16),
                           index_t element_bytes = sizeof(conduit::int16),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }
 

    void set_path_external(const std::string &path,
                           int32 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int32),
                           index_t element_bytes = sizeof(conduit::int32),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           int64 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::int64),
                           index_t element_bytes = sizeof(conduit::int64),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           uint8  *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint8),
                           index_t element_bytes = sizeof(conduit::uint8),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           uint16 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint16),
                           index_t element_bytes = sizeof(conduit::uint16),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }

                           
    void set_path_external(const std::string &path,
                           uint32 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint32),
                           index_t element_bytes = sizeof(conduit::uint32),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }

                           
    void set_path_external(const std::string &path,
                           uint64 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint64),
                           index_t element_bytes = sizeof(conduit::uint64),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }

                           
    void set_path_external(const std::string &path,
                           float32 *data,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::float32),
                           index_t element_bytes = sizeof(conduit::float32),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           float64 *data, 
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::float64),
                           index_t element_bytes = sizeof(conduit::float64),
                           index_t endianness = Endianness::DEFAULT_T)
                           {fetch(path).set_external(data,
                                                     num_elements,
                                                     offset,
                                                     stride,
                                                     element_bytes,
                                                     endianness);
                           }


    void set_path_external(const std::string &path,
                           std::vector<int8> &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<int16> &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<int32> &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<int64> &data)
                     {fetch(path).set_external(data);}

    void set_path_external(const std::string &path,
                           std::vector<uint8>   &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<uint16>  &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<uint32>  &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<uint64>  &data)
                     {fetch(path).set_external(data);}

    void set_path_external(const std::string &path,
                           std::vector<float32> &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           std::vector<float64> &data)
                     {fetch(path).set_external(data);}

    void set_path_external(const std::string &path,
                           const bool8_array  &data)
                     {fetch(path).set_external(data);} 

    void set_path_external(const std::string &path,
                           const int8_array  &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const int16_array &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const int32_array &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const int64_array &data)
                     {fetch(path).set_external(data);}

    void set_path_external(const std::string &path,
                           const uint8_array  &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const uint16_array &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const uint32_array &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const uint64_array &data)
                     {fetch(path).set_external(data);}

    void set_path_external(const std::string &path,
                           const float32_array &data)
                     {fetch(path).set_external(data);}
    void set_path_external(const std::string &path,
                           const float64_array &data)
                     {fetch(path).set_external(data);}

    // bytestr use cases:
    void set_path_external(const std::string &path,
                           char *data, 
                           index_t dtype_id,
                           index_t num_elements = 1,
                           index_t offset = 0,
                           index_t stride = sizeof(conduit::uint8),
                           index_t element_bytes = sizeof(conduit::uint8),
                           index_t endianness = Endianness::DEFAULT_T)
                        {fetch(path).set_external(data,
                                                  dtype_id,
                                                  num_elements,
                                                  offset,
                                                  stride,
                                                  element_bytes,
                                                  endianness);}


    ///@}
    // -- end set_path_external --

    // -- begin assignment ops --
    /** @name Node assignment operators
      * &operator=(...) methods use set(...) (copy) semantics
      */
    ///@{                               
    Node &operator=(const Node &node);
    Node &operator=(DataType dtype);

    ///
    /// Note: there is not bool8 operator b/c any pointer type
    /// in c++ will impliclity cast to bool (which is one of the end points for bool)
    ///

    Node &operator=(int8 data);
    Node &operator=(int16 data);
    Node &operator=(int32 data);
    Node &operator=(int64 data);

    Node &operator=(uint8 data);
    Node &operator=(uint16 data);
    Node &operator=(uint32 data);
    Node &operator=(uint64 data);

    Node &operator=(float32 data);    
    Node &operator=(float64 data);

    Node &operator=(const std::vector<int8>   &data);
    Node &operator=(const std::vector<int16>   &data);
    Node &operator=(const std::vector<int32>   &data);
    Node &operator=(const std::vector<int64>   &data);

    Node &operator=(const std::vector<uint8>   &data);
    Node &operator=(const std::vector<uint16>   &data);
    Node &operator=(const std::vector<uint32>   &data);
    Node &operator=(const std::vector<uint64>   &data);

    Node &operator=(const std::vector<float32>  &data);
    Node &operator=(const std::vector<float64>  &data);

    Node &operator=(const int8_array  &data);
    Node &operator=(const int16_array &data);
    Node &operator=(const int32_array &data);
    Node &operator=(const int64_array &data);

    Node &operator=(const uint8_array  &data);
    Node &operator=(const uint16_array &data);
    Node &operator=(const uint32_array &data);
    Node &operator=(const uint64_array &data);

    Node &operator=(const float32_array &data);
    Node &operator=(const float64_array &data);

    // bytestr use cases:
    Node &operator=(const char *data);
    Node &operator=(const std::string &data);

    ///@}
    // -- end assignment ops --

    NodeIterator     iterator();
    /*schema access */
    const Schema     &schema() const { return *m_schema;}   

    Schema           *schema_pointer() {return m_schema;}   

    /* data access */
    uint8            *data_pointer() {return (uint8*)m_data;}

    /* parent access */
    bool             has_parent() const {return m_parent != NULL;}
    Node            *parent() {return m_parent;}
    
    /* Info */
    index_t           total_bytes() const { return m_schema->total_bytes();}
    index_t           total_bytes_compact() const { return m_schema->total_bytes_compact();}
    const DataType   &dtype() const       { return m_schema->dtype();}
    
    /* serialization */
    void        serialize(std::vector<uint8> &data) const;
    void        serialize(const std::string &stream_path) const;
    
    // In the future, support our own IOStreams (which will provide single interface 
    // for bin,hdf,silo end-points.
    void        serialize(std::ofstream &ofs) const;
    void        save(const std::string &obase) const;
    

    // compact this node
    void        compact();
    // compact into a new node
    void        compact_to(Node &n_dest) const;
    
    // this will be ineff w/o move semantics, but is very conv 
    Node        compact_to() const;
    
    bool        is_compact() const {return dtype().is_compact();}

    void        info(Node &nres) const;
    // this will be ineff w/o move semantics, but is very conv 
    Node        info() const;

    /// update() adds entries from n_src to current Node (like python dict update) 
    /// the input should be const, but the lack of a const fetch prevents this for now
    void        update(Node &n_src);
    ///
    /// TODO:
    ///  bool        compare(const Node &n, Node &cmp_results) const;
    ///  bool        operator==(const Node &n) const;


    // -- begin entry access --
    /// @name Node::fetch(...) methods
    ///@{
    // Note: `fetch' methods do modify map structure if a path doesn't exist
    Node             &fetch(const std::string &path);
    Node             &fetch(index_t idx);
    
    Node             *fetch_pointer(const std::string &path);
    Node             *fetch_pointer(index_t idx);

    ///@}
    // -- end entry access --


    // -- begin list append interface methods --
    /// @name Node list append inteface methods
    /// @{
    void append()
        {list_append(Node());}

    void append(const Node &node)
        {list_append(Node(node));}

    void append(const DataType &data)
        {list_append(Node(data));}

    void append(int8 data)
        {list_append(Node(data));}
    void append(int16 data)
        {list_append(Node(data));}
    void append(int32 data)
        {list_append(Node(data));}
    void append(int64 data)
        {list_append(Node(data));}

    void append(uint8 data)
        {list_append(Node(data));}
    void append(uint16 data)
        {list_append(Node(data));}
    void append(uint32 data)
        {list_append(Node(data));}
    void append(uint64 data)
        {list_append(Node(data));}
    void append(float32 data)
        {list_append(Node(data));}
    void append(float64 data)
        {list_append(Node(data));}

    void append(const std::vector<int8>   &data)
        {list_append(Node(data));}
    void append(const std::vector<int16>  &data)
        {list_append(Node(data));}
    void append(const std::vector<int32>  &data)
        {list_append(Node(data));}
    void append(const std::vector<int64>  &data)
        {list_append(Node(data));}

    void append(const std::vector<uint8>   &data)
        {list_append(Node(data));}
    void append(const std::vector<uint16>  &data)
        {list_append(Node(data));}
    void append(const std::vector<uint32>  &data)
        {list_append(Node(data));}
    void append(const std::vector<uint64>  &data)
        {list_append(Node(data));}
    void append(const std::vector<float32> &data)
        {list_append(Node(data));}
    void append(const std::vector<float64> &data)
        {list_append(Node(data));}

    void append(const bool8_array  &data)
        {list_append(Node(data));}

    void append(const int8_array  &data)
        {list_append(Node(data));}
    void append(const int16_array &data)
        {list_append(Node(data));}
    void append(const int32_array &data)
        {list_append(Node(data));}
    void append(const int64_array &data)
        {list_append(Node(data));}

    void append(const uint8_array  &data)
        {list_append(Node(data));}
    void append(const uint16_array &data)
        {list_append(Node(data));}
    void append(const uint32_array &data)
        {list_append(Node(data));}
    void append(const uint64_array &data)
        {list_append(Node(data));}

    void append(const float32_array &data)
        {list_append(Node(data));}
    void append(const float64_array &data)
        {list_append(Node(data));}
    
    void append(const std::string &data)
        {
            index_t idx = m_children.size(); 
            append();
            m_children[idx]->set(data);
        }

    // -- end list append interface methods --
    ///@}

    index_t number_of_entries() const;
    void    remove(index_t idx);
    void    remove(const std::string &path);
    
    bool    has_path(const std::string &path) const;
    void    paths(std::vector<std::string> &paths) const;


    // these support the map and list interfaces
    Node             &operator[](const std::string &path);
    Node             &operator[](const index_t idx);

    // TODO crs methods to all types ?
    int64            to_int64()   const;
    uint64           to_uint64()  const;
    float64          to_float64() const;
    index_t          to_index_t() const;
        
    std::string         to_json(bool detailed=true, 
                                index_t indent=2, 
                                index_t depth=0,
                                const std::string &pad=" ",
                                const std::string &eoe="\n") const;

    void                to_json(std::ostringstream &oss,
                                bool detailed=true, 
                                index_t indent=2, 
                                index_t depth=0,
                                const std::string &pad=" ",
                                const std::string &eoe="\n") const;


     std::string      to_pure_json(index_t indent=2) const
                        {return to_json(false,indent);}

     void             to_pure_json(std::ostringstream &oss,
                              index_t indent=2) const
                        {to_json(oss,false,indent);}

    std::string      to_simple_json(index_t indent=2,
                                    index_t depth=0,
                                    const std::string &pad=" ",
                                    const std::string &eoe="\n") const
                            {return to_json(false,indent,depth,pad,eoe);}

    void             to_simple_json(std::ostringstream &oss,
                                    index_t indent=2, 
                                    index_t depth=0,
                                    const std::string &pad=" ",
                                    const std::string &eoe="\n") const
                            {to_json(oss,false,indent,depth,pad,eoe);}
                                                                
    std::string      to_detailed_json(index_t indent=2, 
                                      index_t depth=0,
                                      const std::string &pad=" ",
                                      const std::string &eoe="\n") const
                     {return to_json(true,indent,depth,pad,eoe);}

    void             to_detailed_json(std::ostringstream &oss,
                                      index_t indent=2, 
                                      index_t depth=0,
                                      const std::string &pad=" ",
                                      const std::string &eoe="\n") const
                     {to_json(oss,true,indent,depth,pad,eoe);}


    void              print(bool detailed=false) const
                        {std::cout << to_json(detailed,2) << std::endl;}

    void              print_detailed() const
                        {print(true);}

    // -- begin value access --    
    /// @name Node::as_{dtype}(...) methods
    ///@{
    bool8            as_bool8()   const { return *((bool8*)element_pointer(0));}

    int8             as_int8()   const  { return *((int8*)element_pointer(0));}
    int16            as_int16()  const  { return *((int16*)element_pointer(0));}
    int32            as_int32()  const  { return *((int32*)element_pointer(0));}
    int64            as_int64()  const  { return *((int64*)element_pointer(0));}

    uint8            as_uint8()   const { return *((uint8*)element_pointer(0));}
    uint16           as_uint16()  const { return *((uint16*)element_pointer(0));}
    uint32           as_uint32()  const { return *((uint32*)element_pointer(0));}
    uint64           as_uint64()  const { return *((uint64*)element_pointer(0));}

    float32          as_float32() const { return *((float32*)element_pointer(0));}
    float64          as_float64() const { return *((float64*)element_pointer(0));}

    bool8           *as_bool8_ptr()    { return (bool8*)element_pointer(0);}

    int8            *as_int8_ptr()     { return (int8*)element_pointer(0);}
    int16           *as_int16_ptr()    { return (int16*)element_pointer(0);}
    int32           *as_int32_ptr()    { return (int32*)element_pointer(0);}
    int64           *as_int64_ptr()    { return (int64*)element_pointer(0);}

    uint8           *as_uint8_ptr()    { return (uint8*)element_pointer(0);}
    uint16          *as_uint16_ptr()   { return (uint16*)element_pointer(0);}
    uint32          *as_uint32_ptr()   { return (uint32*)element_pointer(0);}
    uint64          *as_uint64_ptr()   { return (uint64*)element_pointer(0);}
        
    float32         *as_float32_ptr()  { return (float32*)element_pointer(0);}
    float64         *as_float64_ptr()  { return (float64*)element_pointer(0);}
    
    bool8_array      as_bool8_array()  { return bool8_array(m_data,dtype());}
    
    int8_array       as_int8_array()   { return int8_array(m_data,dtype());}
    int16_array      as_int16_array()  { return int16_array(m_data,dtype());}
    int32_array      as_int32_array()  { return int32_array(m_data,dtype());}
    int64_array      as_int64_array()  { return int64_array(m_data,dtype());}

    uint8_array      as_uint8_array()  { return uint8_array(m_data,dtype());}
    uint16_array     as_uint16_array() { return uint16_array(m_data,dtype());}
    uint32_array     as_uint32_array() { return uint32_array(m_data,dtype());}
    uint64_array     as_uint64_array() { return uint64_array(m_data,dtype());}

    float32_array    as_float32_array() { return float32_array(m_data,dtype());}
    float64_array    as_float64_array() { return float64_array(m_data,dtype());}

    bool8_array      as_bool8_array() const { return bool8_array(m_data,dtype());}
    
    int8_array       as_int8_array()  const { return int8_array(m_data,dtype());}
    int16_array      as_int16_array() const { return int16_array(m_data,dtype());}
    int32_array      as_int32_array() const { return int32_array(m_data,dtype());}
    int64_array      as_int64_array() const { return int64_array(m_data,dtype());}

    uint8_array      as_uint8_array()  const { return uint8_array(m_data,dtype());}
    uint16_array     as_uint16_array() const { return uint16_array(m_data,dtype());}
    uint32_array     as_uint32_array() const { return uint32_array(m_data,dtype());}
    uint64_array     as_uint64_array() const { return uint64_array(m_data,dtype());}

    float32_array    as_float32_array() const { return float32_array(m_data,dtype());}
    float64_array    as_float64_array() const { return float64_array(m_data,dtype());}

    char            *as_char8_str() {return (char *)element_pointer(0);}
    const char      *as_char8_str() const {return (const char *)element_pointer(0);}
    
    std::string      as_string() const {return std::string(as_char8_str());}

    // -- end value access --    
    ///@}


    // these are used for construction by the Node & Generator classes
    void             set_data_pointer(void *data_ptr);
    void             set_schema_pointer(Schema *schema_ptr);
    void             append_node_pointer(Node *node)
                        {m_children.push_back(node);}
    void             set_parent(Node *parent) { m_parent = parent;}

private:
    // -- helpers for init, memory allocation, and cleanup --  
    void             init(const DataType &dtype);
    void             allocate(index_t dsize);
    void             allocate(const DataType &dtype);
    void             mmap(const std::string &stream_path, index_t dsize);
    void             cleanup();
    void             release();

    static void      walk_schema(Node   *node,
                                 Schema *schema,
                                 void   *data,
                                 bool    copy_data);
   
    void            *element_pointer(index_t idx)
                     {return static_cast<char*>(m_data) + dtype().element_index(idx);};
    const void      *element_pointer(index_t idx) const 
                     {return static_cast<char*>(m_data) + dtype().element_index(idx);};

    void              serialize(uint8 *data, index_t curr_offset) const;
    void              info(Node &res, const std::string &curr_path) const;
    void              set_node_using_schema_pointer(const Node &node, Schema *schema);

    void              compact_to(uint8 *data, index_t curr_offset) const;

    // for leaf types
    void              compact_elements_to(uint8 *data) const;

    /* init helpers */
    void              init_defaults();
    void              init_list();
    void              init_object();
    void              list_append(const Node &node);

    Node                *m_parent;
    Schema              *m_schema;
    std::vector<Node*>   m_children;

    // TODO: DataContainer
    void     *m_data;
    index_t   m_data_size;

    bool      m_alloced;
    bool      m_mmaped;
    int       m_mmap_fd;
};

}


#endif
