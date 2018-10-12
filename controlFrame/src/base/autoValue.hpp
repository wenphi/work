#pragma once
#include <list>
#include <iostream>
class autoValue
{
public:
  autoValue(){};
  ~autoValue(){};
};
// class autoValue
// {
// public:
//   enum Kind
//   {
//     t_empty,
//     t_integer,
//     t_string,
//     t_bool,
//     t_symbol,
//     t_dynamic,
//     t_float /*, t_list, t_map */
//   };

//   typedef std::list<autoValue *> List;
//   //    typedef std::map<std::string, Value> Map;

//   autoValue();
//   autoValue(Kind k);
//   autoValue(bool v);
//   autoValue(long v);
//   autoValue(int v);
//   autoValue(unsigned int v);
//   autoValue(unsigned long v);
//   autoValue(float v);
//   autoValue(double v);
//   autoValue(const char *str, Kind k = t_symbol);
//   autoValue(std::string str, Kind k = t_symbol);
//   autoValue(const autoValue &other);
//   // autoValue(DynamicValue *dv);
//   // autoValue(DynamicValue &dv);
//   virtual ~autoValue();
//   std::string asString() const;
//   std::string quoted() const;
//   bool asFloat(double &val) const;
//   bool asInteger(long &val) const;
//   bool asBoolean(bool &val) const;
//   long trunc() const;
//   long round(int digits = 0) const;
//   double toFloat() const;
//   explicit operator long() { return iValue; }
//   explicit operator int() { return (int)iValue; }
//   explicit operator float() { return (float)fValue; }
//   explicit operator double() { return fValue; }
//   //	Value operator[](int index);
//   //	Value operator[](std::string index);

//   Kind kind;
//   bool bValue;
//   long iValue;
//   double fValue;
//   std::string sValue; // used for strings and for symbols
//   // MachineInstance *cached_machine;
//   // DynamicValue *dyn_value;
//   autoValue *cached_value;
//   int token_id;

//   // DynamicValue *dynamicValue() const { return dyn_value; }
//   // void setDynamicValue(DynamicValue *dv);
//   // void setDynamicValue(DynamicValue &dv);

//   autoValue &operator=(const autoValue &orig);
//   autoValue &operator=(bool);
//   autoValue &operator=(int);
//   autoValue &operator=(long);
//   autoValue &operator=(unsigned long);
//   autoValue &operator=(const char *);
//   autoValue &operator=(std::string);
//   autoValue &operator=(float);
//   autoValue &operator=(double);

//   bool operator>=(const autoValue &other) const;
//   bool operator<=(const autoValue &other) const;
//   bool operator<(const autoValue &other) const { return !operator>=(other); }
//   bool operator>(const autoValue &other) const { return !operator<=(other); }
//   bool operator==(const autoValue &other) const;
//   bool operator!=(const autoValue &other) const;
//   bool operator&&(const autoValue &other) const;
//   bool operator||(const autoValue &other) const;
//   bool operator!() const;
//   autoValue operator-(void) const;
//   autoValue &operator+(const autoValue &other);
//   autoValue &operator-(const autoValue &other);
//   autoValue &operator*(const autoValue &other);
//   autoValue &operator/(const autoValue &other);
//   autoValue &operator%(const autoValue &other);
//   autoValue &operator&(const autoValue &other);
//   autoValue &operator|(const autoValue &other);
//   autoValue &operator^(const autoValue &other);
//   autoValue &operator~();

//   std::ostream &operator<<(std::ostream &out) const;

// private:
//   std::string name() const;
// };