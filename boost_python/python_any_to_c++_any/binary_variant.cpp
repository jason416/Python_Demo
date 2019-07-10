#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

#include "variant.h"
#include "variant_visitor.h"


namespace 
{
    using namespace Variant_test;

template<typename T>
bool Compare(const Variant & lhs, const Variant & rhs)
{
  return lhs.As<T>() == rhs.As<T>();
}
}

namespace Variant_test
{

//---------------------------------------------------
// Variant
//---------------------------------------------------

bool Variant::operator== (const Variant & var) const
{
  if (Value.empty() ^ var.Value.empty())
    {
      return false;
    }

  if (Value.empty() && var.Value.empty())
    {
      return true;
    }

  if (Value.type() != var.Value.type())
    {
      return false;
    }

  using namespace boost;
  const std::type_info & t = Value.type();

  if (t == typeid(bool))
    { return Compare<bool>(*this, var); }

  else if (t == typeid(std::vector<bool>))
    { return Compare<std::vector<bool>>(*this, var); }

  else if (t == typeid(int8_t))
    { return Compare<int8_t>(*this, var); }

  else if (t == typeid(std::vector<int8_t>))
    { return Compare<std::vector<int8_t>>(*this, var); }

  else if (t == typeid(uint8_t))
    { return Compare<uint8_t>(*this, var); }

  else if (t == typeid(std::vector<uint8_t>))
    { return Compare<std::vector<uint8_t>>(*this, var); }

  else if (t == typeid(int16_t))
    { return Compare<int16_t>(*this, var); }

  else if (t == typeid(std::vector<int16_t>))
    { return Compare<std::vector<int16_t>>(*this, var); }

  else if (t == typeid(uint16_t))
    { return Compare<uint16_t>(*this, var); }

  else if (t == typeid(std::vector<uint16_t>))
    { return Compare<std::vector<uint16_t>>(*this, var); }

  else if (t == typeid(int32_t))
    { return Compare<int32_t>(*this, var); }

  else if (t == typeid(std::vector<int32_t>))
    { return Compare<std::vector<int32_t>>(*this, var); }

  else if (t == typeid(uint32_t))
    { return Compare<uint32_t>(*this, var); }

  else if (t == typeid(std::vector<uint32_t>))
    { return Compare<std::vector<uint32_t>>(*this, var); }

  else if (t == typeid(int64_t))
    { return Compare<int64_t>(*this, var); }

  else if (t == typeid(std::vector<int64_t>))
    { return Compare<std::vector<int64_t>>(*this, var); }

  else if (t == typeid(uint64_t))
    { return Compare<uint64_t>(*this, var); }

  else if (t == typeid(std::vector<uint64_t>))
    { return Compare<std::vector<uint64_t>>(*this, var); }

  else if (t == typeid(float))
    { return Compare<float>(*this, var); }

  else if (t == typeid(std::vector<float>))
    { return Compare<std::vector<float>>(*this, var); }

  else if (t == typeid(double))
    { return Compare<double>(*this, var); }

  else if (t == typeid(std::vector<double>))
    { return Compare<std::vector<double>>(*this, var); }

  else if (t == typeid(std::string))
    { return Compare<std::string>(*this, var); }

  else if (t == typeid(std::vector<std::string>))
    { return Compare<std::vector<std::string>>(*this, var); }

  /*
      else if (t == typeid(DataValue))
        return Compare<DataValue>(*this, Value);
      else if (t == typeid(std::vector<DataValue>))
        return Compare<std::vector<DataValue>>(*this, var);
  */
  else if (t == typeid(Variant))
    { return Compare<Variant>(*this, var); }

  else if (t == typeid(std::vector<Variant>))
    { return Compare<std::vector<Variant>>(*this, var); }

  throw std::logic_error(std::string("Unknown variant type '") + t.name() + std::string("'."));
}

bool Variant::IsScalar() const
{
  return !IsArray();
}

bool Variant::IsNul() const
{
  return Value.empty();
}

bool Variant::IsArray() const
{
  const std::type_info & t = Value.type();
  return
    (t == typeid(std::vector<bool>))       ||
    (t == typeid(std::vector<int8_t>))     ||
    (t == typeid(std::vector<uint8_t>))    ||
    (t == typeid(std::vector<int16_t>))    ||
    (t == typeid(std::vector<uint16_t>))   ||
    (t == typeid(std::vector<int32_t>))    ||
    (t == typeid(std::vector<uint32_t>))   ||
    (t == typeid(std::vector<int64_t>))    ||
    (t == typeid(std::vector<uint64_t>))   ||
    (t == typeid(std::vector<float>))      ||
    (t == typeid(std::vector<double>))     ||
    (t == typeid(std::vector<std::string>)) ||
//    (t == typeid(std::vector<DataValue>))  ||
    (t == typeid(std::vector<Variant>));
}

VariantType Variant::Type() const
{
  if (Value.empty())
    { return VariantType::NUL; }

  const std::type_info & t = Value.type();

  if (t == typeid(bool) || t == typeid(std::vector<bool>))
    { return VariantType::BOOLEAN; }

  else if (t == typeid(int8_t) || t == typeid(std::vector<int8_t>))
    { return VariantType::SBYTE; }

  else if (t == typeid(uint8_t) || t == typeid(std::vector<uint8_t>))
    { return VariantType::BYTE; }

  else if (t == typeid(int16_t) || t == typeid(std::vector<int16_t>))
    { return VariantType::INT16; }

  else if (t == typeid(uint16_t) || t == typeid(std::vector<uint16_t>))
    { return VariantType::UINT16; }

  else if (t == typeid(int32_t) || t == typeid(std::vector<int32_t>))
    { return VariantType::INT32; }

  else if (t == typeid(uint32_t) || t == typeid(std::vector<uint32_t>))
    { return VariantType::UINT32; }

  else if (t == typeid(int64_t) || t == typeid(std::vector<int64_t>))
    { return VariantType::INT64; }

  else if (t == typeid(uint64_t) || t == typeid(std::vector<uint64_t>))
    { return VariantType::UINT64; }

  else if (t == typeid(float) || t == typeid(std::vector<float>))
    { return VariantType::FLOAT; }

  else if (t == typeid(double) || t == typeid(std::vector<double>))
    { return VariantType::DOUBLE; }

  else if (t == typeid(std::string) || t == typeid(std::vector<std::string>))
    { return VariantType::STRING; }

  /*
      else if (t == typeid(DataValue) || t == typeid(std::vector<DataValue>))
        return VariantType::DATA_VALUE;
  */
  else if (t == typeid(Variant) || t == typeid(std::vector<Variant>))
    { return VariantType::VARIANT; }

  throw std::runtime_error(std::string("Unknown variant type '") + t.name() + "'.");
}


void Variant::Visit(VariantVisitor & visitor) const
{
  using namespace boost;
  const std::type_info & t = Value.type();

  if (t == typeid(bool))
    { visitor.Visit(any_cast<bool>(Value)); }

  else if (t == typeid(std::vector<bool>))
    { visitor.Visit(any_cast<std::vector<bool>>(Value)); }

  else if (t == typeid(int8_t))
    { visitor.Visit(any_cast<int8_t>(Value)); }

  else if (t == typeid(std::vector<int8_t>))
    { visitor.Visit(any_cast<std::vector<int8_t>>(Value)); }

  else if (t == typeid(uint8_t))
    { visitor.Visit(any_cast<uint8_t>(Value)); }

  else if (t == typeid(std::vector<uint8_t>))
    { visitor.Visit(any_cast<std::vector<uint8_t>>(Value)); }

  else if (t == typeid(int16_t))
    { visitor.Visit(any_cast<int16_t>(Value)); }

  else if (t == typeid(std::vector<int16_t>))
    { visitor.Visit(any_cast<std::vector<int16_t>>(Value)); }

  else if (t == typeid(uint16_t))
    { visitor.Visit(any_cast<uint16_t>(Value)); }

  else if (t == typeid(std::vector<uint16_t>))
    { visitor.Visit(any_cast<std::vector<uint16_t>>(Value)); }

  else if (t == typeid(int32_t))
    { visitor.Visit(any_cast<int32_t>(Value)); }

  else if (t == typeid(std::vector<int32_t>))
    { visitor.Visit(any_cast<std::vector<int32_t>>(Value)); }

  else if (t == typeid(uint32_t))
    { visitor.Visit(any_cast<uint32_t>(Value)); }

  else if (t == typeid(std::vector<uint32_t>))
    { visitor.Visit(any_cast<std::vector<uint32_t>>(Value)); }

  else if (t == typeid(int64_t))
    { visitor.Visit(any_cast<int64_t>(Value)); }

  else if (t == typeid(std::vector<int64_t>))
    { visitor.Visit(any_cast<std::vector<int64_t>>(Value)); }

  else if (t == typeid(uint64_t))
    { visitor.Visit(any_cast<uint64_t>(Value)); }

  else if (t == typeid(std::vector<uint64_t>))
    { visitor.Visit(any_cast<std::vector<uint64_t>>(Value)); }

  else if (t == typeid(float))
    { visitor.Visit(any_cast<float>(Value)); }

  else if (t == typeid(std::vector<float>))
    { visitor.Visit(any_cast<std::vector<float>>(Value)); }

  else if (t == typeid(double))
    { visitor.Visit(any_cast<double>(Value)); }

  else if (t == typeid(std::vector<double>))
    { visitor.Visit(any_cast<std::vector<double>>(Value)); }

  else if (t == typeid(std::string))
    { visitor.Visit(any_cast<std::string>(Value)); }

  else if (t == typeid(std::vector<std::string>))
    { visitor.Visit(any_cast<std::vector<std::string>>(Value)); }

  /*
      else if (t == typeid(DataValue))
        visitor.Visit(any_cast<DataValue>(Value));
      else if (t == typeid(std::vector<DataValue>))
        visitor.Visit(any_cast<std::vector<DataValue>>(Value));
        //Variant of variant is not allowed but variant of an array of variant is OK
      else if (t == typeid(Variant))
        visitor.Visit(any_cast<Variant>(Value));
  */
  else if (t == typeid(std::vector<Variant>))
    { visitor.Visit(any_cast<std::vector<Variant>>(Value)); }

  else
    { throw std::runtime_error(std::string("Unknown variant type '") + t.name() + "'."); }
}


std::string Variant::ToString() const
{
  if (IsScalar())
    {
      std::stringstream _str;

      switch (Type())
        {
        case VariantType::STRING:
          _str << boost::any_cast<std::string> (Value);
          break;

        case VariantType::BOOLEAN:
          _str << ((boost::any_cast<bool> (Value)) ? "true" : "false");
          break;

        case VariantType::BYTE:
          _str << boost::any_cast<unsigned char> (Value);
          break;

        case VariantType::SBYTE:
          _str << boost::any_cast<char> (Value);
          break;

        case VariantType::DOUBLE:
          _str << boost::any_cast<double> (Value);
          break;

        case VariantType::FLOAT:
          _str << boost::any_cast<float> (Value);
          break;

        case VariantType::INT16:
          _str << boost::any_cast<int16_t> (Value);
          break;

        case VariantType::INT32:
          _str << boost::any_cast<int32_t> (Value);
          break;

        case VariantType::INT64:
          _str << boost::any_cast<int64_t> (Value);
          break;

        case VariantType::UINT16:
          _str << boost::any_cast<uint16_t> (Value);
          break;

        case VariantType::UINT32:
          _str << boost::any_cast<uint32_t> (Value);
          break;

        case VariantType::UINT64:
          _str << boost::any_cast<uint64_t> (Value);
          break;

        default:
          _str << "conversion to string is not supported";
          break;
        }

      return _str.str();
    }

  else
    {
      return "conversion to string is not supported"; //TODO - add implementation for conversion
    }
}
}
