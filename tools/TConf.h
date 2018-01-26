/////////////////////////////////////////////
///COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file TConf.h
/// @brief 配置文件读写操作类
///
/// 通过[group]和key，获取和设置value的值
///
/// @version 1.0
/// @author liukang
/// @date 2017.12.15
//////////////////////////////////////////////
#pragma once

#include <string>
#include <map>

namespace WebTool {

/// 本类的功能：配置文件读写接口
class  TConf
{
public:
    /// @param configName 配置文件名
    /// @note  初始化带上配置文件路径全名
    TConf(const std::string &configName);
    ~TConf();

    /// @brief  通过[group]和key，获取value的值
    /// @param  group 组名，一般为“[group]”
    /// @param  key 属性键值key
    /// @param  valueDefault 默认的value值
    /// @return 返回读取到配置中的value值
    std::string getConfStr(const std::string &group, const std::string &key, const std::string &valueDefault = "");

    /// @brief  通过[group]和key，设置value的值
    /// @param  group 组名，一般为“[group]”
    /// @param  key 属性键值key
    /// @param  value 设置的value值
    /// @return 是否设置成功
    bool setConfStr(const std::string &group, const std::string &key, const std::string &value);

    /// @brief  删除[group]下的key属性
    /// @param  group 组名，一般为“[group]”
    /// @param  key 属性键值key
    void delKey(const std::string &group, const std::string &key);

    /// @brief  删除[group]组下所有配置属性
    /// @param  group 组名，一般为“[group]”
    void delGroup(const std::string &group);

private:

    /// @brief  从文件读取配置
    void readConfig();

    /// @brief  保存配置到文件
    void saveConfig();

    typedef std::map<std::string, std::string> KeyValueDef;
    typedef std::map<std::string, KeyValueDef> GroupDef;

    ///配置文件路径全名
    std::string m_configName;

    ///保存配置的map数据结构
    GroupDef m_groupConfig;
};

} //namespace WebTool


