#pragma once
#include <vector>
#include <jsoncpp/json/json.h>
#include "autoValue.hpp"

class actionBase
{
  public:
    actionBase() {}
    virtual ~actionBase() {}
    //子类调用
    void start()
    {
        run(jsonData);
    }
    bool setParams(std::vector<autoValue> params_)
    {
        std::copy(params_.begin(), params_.end(), std::back_inserter(actionParams));
        return true;
    };
    bool setParams(Json::Value &jsonData_)
    {
        jsonData = jsonData_;
        return true;
    }

  private:
    virtual bool run(std::vector<autoValue> params) { return true; };
    virtual bool run(Json::Value &cmdData) = 0;
    std::vector<autoValue> actionParams;
    Json::Value jsonData;
};