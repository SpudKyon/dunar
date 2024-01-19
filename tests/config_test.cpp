//
// Created by spud on 24-1-19.
//

#include "config.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <yaml-cpp/yaml.h>

dunar::ConfigVar<int>::ptr g_int_value_config =
    dunar::Config::Lookup("system.port", (int)8080, "system port");

dunar::ConfigVar<float>::ptr g_float_value_config =
    dunar::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::Node& node, int level) {
  if (node.IsScalar()) {
    DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
        << std::string(level * 4, ' ') << node.Scalar() << " - " << node.Type()
        << " - " << level;
  } else if (node.IsNull()) {
    DUNAR_LOG_INFO(DUNAR_LOG_ROOT()) << std::string(level * 4, ' ') << "NULL - "
                                     << node.Type() << " - " << level;
  } else if (node.IsMap()) {
    for (auto it = node.begin(); it != node.end(); ++it) {
      DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
          << std::string(level * 4, ' ') << it->first << " - "
          << it->second.Type() << " - " << level;
      print_yaml(it->second, level + 1);
    }
  } else if (node.IsSequence()) {
    for (size_t i = 0; i < node.size(); ++i) {
      DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
          << std::string(level * 4, ' ') << i << " - " << node[i].Type()
          << " - " << level;
      print_yaml(node[i], level + 1);
    }
  }
}

TEST(ConfigTest, LOADTEST) {
  YAML::Node root =
      YAML::LoadFile("/home/spud/proj/CLionProjects/dunar/resources/log.yml");
  print_yaml(root, 0);

  DUNAR_LOG_INFO(DUNAR_LOG_ROOT()) << root.Scalar();
}

TEST(ConfigTest, CONFIGTEST) {
  DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
      << "before: " << g_int_value_config->getValue();
  DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
      << "before: " << g_float_value_config->toString();

  YAML::Node root =
      YAML::LoadFile("/home/spud/proj/CLionProjects/dunar/resources/log.yml");
  dunar::Config::LoadFromYaml(root);

  DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
      << "after: " << g_int_value_config->getValue();
  DUNAR_LOG_INFO(DUNAR_LOG_ROOT())
      << "after: " << g_float_value_config->toString();
}