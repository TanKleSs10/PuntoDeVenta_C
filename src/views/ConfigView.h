#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include "../models/ConfigModel.h"

// Declaraciones para ConfigView (view)

void inputConfigData(ConfigPOS *c);

void showConfigData(const ConfigPOS *c);

int confirmDeleteConfig();

void showNoConfigMessage();
#endif
