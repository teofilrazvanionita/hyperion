#!/bin/bash


mysql -u root -p < ./hyperion.sql
mysql -u root -p poesis < ./TableDef_users.sql

