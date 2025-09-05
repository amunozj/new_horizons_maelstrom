void LocationInitBermudes(ref n)
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ГОРОД
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_town";
locations[n].id.label = "#stown_name#";
locations[n].worldmap = "Bermudes_town";
locations[n].townsack = "Bermudes";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
locations[n].filespath.models = "locations\Town_IslaMona\Town";
locations[n].image = "loading\towns\pearl1.tga.tx";
//Sound
locations[n].type = "town";
//Models
//Always
locations[n].models.always.town = "IslaMona";
locations[n].models.always.town.sea_reflection = 1;
Locations[n].models.always.town.foam = "1";
locations[n].models.always.locators = "IslaMona_locators";
locations[n].models.always.grassPatch = "IslaMona_grass";
locations[n].models.always.seabed = "IslaMona_sb";
Locations[n].models.always.seabed.foam = "1";
locations[n].models.always.plan = "IslaMona_plan";
locations[n].models.always.plan.level = 9;
//River
locations[n].models.always.Waterfall1 = "Islamona_river1";
locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
locations[n].models.always.Waterfall1.level = 50;
locations[n].models.always.Waterfall2 = "Islamona_river2";
locations[n].models.always.Waterfall2.uvslide.v0 = -0.3;
locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
locations[n].models.always.Waterfall2.level = 49;
//Day
locations[n].models.day.fonar = "IslaMona_fd";
locations[n].models.day.charactersPatch = "IslaMona_patch";
//locations[n].models.day.rinok = "IslaMona_rinok";
//Night
locations[n].models.night.fonar = "IslaMona_fn";
locations[n].models.night.charactersPatch = "IslaMona_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "true";
//Reload map
// --> Типовые городские локации, четкая фиксация на 10 номеров.
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes";
locations[n].reload.l1.emerge = "reload_1";
locations[n].reload.l1.autoreload = "0";
if (VISIT_DECK == 1)
Locations[n].reload.l1.label = "Ship.";
else
Locations[n].reload.l1.label = "Sea.";
locations[n].locators_radius.reload.reload1_back = 1.8;
locations[n].reload.l3.name = "reload3_back";
locations[n].reload.l3.go = "Bermudes_townhall";
locations[n].reload.l3.emerge = "reload1";
locations[n].reload.l3.autoreload = "0";
locations[n].reload.l3.label = "Residence";
locations[n].reload.l4.name = "reload4_back";
locations[n].reload.l4.go = "Bermudes_tavern";
locations[n].reload.l4.emerge = "reload1";
locations[n].reload.l4.autoreload = "0";
locations[n].reload.l4.label = "Tavern";
locations[n].reload.l5.name = "reload5_back";
locations[n].reload.l5.go = "Bermudes_shipyard";
locations[n].reload.l5.emerge = "reload1";
locations[n].reload.l5.autoreload = "0";
locations[n].reload.l5.label = "Shipyard";
locations[n].reload.l5.close_for_night = 1;
locations[n].reload.l6.name = "reload6_back";
locations[n].reload.l6.go = "Bermudes_store";
locations[n].reload.l6.emerge = "reload1";
locations[n].reload.l6.autoreload = "0";
locations[n].reload.l6.label = "Store";
locations[n].reload.l6.close_for_night = 1;
// --> Квестовые локации.
locations[n].reload.l11.name = "houseF1"; //дом, в котором сядет Атилла
locations[n].reload.l11.go = "Bermudes_houseF1";
locations[n].reload.l11.emerge = "reload1";
locations[n].reload.l11.autoreload = "0";
locations[n].reload.l11.label = "House";
locations[n].reload.l12.name = "houseS1"; //дом по пятому квесту пиратки
locations[n].reload.l12.go = "Bermudes_houseS1";
locations[n].reload.l12.emerge = "reload1";
locations[n].reload.l12.autoreload = "0";
locations[n].reload.l12.label = "Orry_House";
// --> Комоны, загрушки. Номера с начинаются с 20.
locations[n].reload.l20.name = "houseH1";
locations[n].reload.l20.go = "Bermudes_Hut1";
locations[n].reload.l20.emerge = "reload1";
locations[n].reload.l20.autoreload = "0";
locations[n].reload.l20.label = "House";
locations[n].reload.l21.name = "houseSp1";
locations[n].reload.l21.go = "Bermudes_Hut2";
locations[n].reload.l21.emerge = "reload1";
locations[n].reload.l21.autoreload = "0";
locations[n].reload.l21.label = "House";
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ТАВЕРНА
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_tavern";
locations[n].id.label = "Tavern";
locations[n].filespath.models = "locations\inside\tavern04";
locations[n].image = "loading\inside\tavern.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "tavern";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].models.always.tavern = "tavern04";
locations[n].models.always.tavern.level = 65538;
locations[n].models.always.locators = "tavern04_locators";
locations[n].models.always.window = "tavern04_window";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
locations[n].models.day.charactersPatch = "tavern04_patch";
//Night
locations[n].models.night.charactersPatch = "tavern04_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "reload4";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_tavern_upstairs";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "Room in #stown_name# tavern.";
//locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
LAi_LocationFightDisable(&locations[n], true);
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// КОМНАТА В ТАВЕРНЕ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_tavern_upstairs";
locations[n].id.label = "Room in #stown_name# tavern."; // KK
locations[n].image = "loading\inside\tavern.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\Tavern_room2";
locations[n].models.always.locators = "Tavern_room2_locators";
locations[n].models.always.tavern = "Tavern_room2";
locations[n].models.always.tavern.level = 65538;
locations[n].models.always.window = "tavern_room2_window";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
locations[n].models.day.charactersPatch = "Tavern_room2_patch";
//Night
locations[n].models.night.charactersPatch = "Tavern_room2_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_tavern";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].locators_radius.reload.reload1 = 0.8;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// МАГАЗИН
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_store";
locations[n].id.label = "Store";
locations[n].filespath.models = "locations\inside\Store02";
locations[n].image = "loading\inside\shop.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "shop";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].models.always.locators = "Store02_locators";
locations[n].models.always.store = "Store02";
locations[n].models.always.store.level = 65538;
locations[n].models.always.window = "Store02_window";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
locations[n].models.day.charactersPatch = "Store02_patch";
//Night
locations[n].models.night.charactersPatch = "Store02_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "reload6";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].reload.l2.name = "reload2";
locations[n].reload.l2.go = "Bermudes_store_room";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "store_room";
LAi_LocationFightDisable(&locations[n], true);
n = n + 1;
locations[n].id = "Bermudes_store_room";
locations[n].id.label = "store_room";
locations[n].image = "loading\inside\shop.tga.tx";
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "shop";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\sklad";
locations[n].models.always.locators = "sklad_locators";
locations[n].models.always.l1 = "sklad";
Locations[n].models.always.window = "sklad_windows";
Locations[n].models.always.window.tech = "LocationWindows";
Locations[n].models.always.window.level = 50;
//Day
locations[n].models.day.charactersPatch = "sklad_patch";
//Night
locations[n].models.night.charactersPatch = "sklad_patch";
//Environment
locations[n].environment.weather = "false";
locations[n].environment.sea = "false";
Locations[n].models.back = "back\farm2_";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_store";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "Store";
LAi_LocationFightDisable(&Locations[n], true);
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ВЕРФЬ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_Shipyard";
locations[n].id.label = "Shipyard";
locations[n].filespath.models = "locations\inside\ShipyardPirates";
locations[n].image = "loading\inside\shipyard.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
//Sound
locations[n].type = "shipyard";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].models.always.locators = "ShipyardPirates_locators";
locations[n].models.always.shipyard = "ShipyardPirates";
locations[n].models.always.shipyard.level = 65538;
locations[n].models.always.rock = "ShipyardPirates_rock";
locations[n].models.always.window = "ShipyardPirates_fn";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
//Day
locations[n].models.day.charactersPatch = "ShipyardPirates_patch";
//Night
locations[n].models.night.charactersPatch = "ShipyardPirates_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "true";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "reload5";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].reload.l2.name = "reload2";
locations[n].reload.l2.go = "Bermudes_Dungeon";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "";
Locations[n].reload.l2.disable = 1;
LAi_LocationFightDisable(&locations[n], true);
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// РЕЗИДЕНЦИЯ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_townhall";
locations[n].id.label = "Townhall";
locations[n].filespath.models = "locations\inside\Residence05";
locations[n].image = "loading\inside\smallresidence.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "residence";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].models.always.locators = "Residence05_locators";
locations[n].models.always.l1 = "Residence05";
locations[n].models.always.l1.level = 65538;
locations[n].models.always.window = "residence05_window";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
locations[n].models.day.charactersPatch = "residence05_patch";
//Night
locations[n].models.night.charactersPatch = "residence05_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "reload3";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].reload.l2.name = "reload2";
locations[n].reload.l2.go = "Bermudes_townhall_room";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "Room";
LAi_LocationFightDisable(&locations[n], true);
n = n + 1;
locations[n].id = "Bermudes_townhall_room";
locations[n].id.label = "Townhall";
Locations[n].image = "Inside_MediumHouse2.tga";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "residence";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\SmallResidence";
locations[n].models.always.locators = "SmallResidence_locators";
locations[n].models.always.house = "SmallResidence";
locations[n].models.always.house.level = 65538;
locations[n].models.always.window = "SmallResidence_windows";
locations[n].models.always.window.tech = "LocationWindows";
locations[n].models.always.window.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
locations[n].models.day.charactersPatch = "SmallResidence_patch";
//Night
locations[n].models.night.charactersPatch = "SmallResidence_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_townhall";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "Townhall";
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Дом, в котором поселится Атилла по Изабелле
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_houseF1";
locations[n].id.label = "Room";
locations[n].image = "loading\inside\mediumhouse01.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\mediumhouse01";
locations[n].models.always.mediumhouse01 = "mediumhouse01";
locations[n].models.always.mediumhouse01.level = 65538;
locations[n].models.day.locators = "mediumhouse01_locators";
locations[n].models.night.locators = "mediumhouse01_Nlocators";
Locations[n].models.always.mediumhouse01windows = "mediumhouse01_windows";
Locations[n].models.always.mediumhouse01windows.tech = "LocationWindows";
locations[n].models.always.mediumhouse01windows.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
Locations[n].models.always.mediumhouse01rand= "mediumhouse01_rand";
locations[n].models.day.charactersPatch = "mediumhouse01_patch";
//Night
locations[n].models.night.charactersPatch = "mediumhouse01_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "houseF1";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Дом по пятому квесту пиратки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_houseS1"; //с комнатой на втором этаже
locations[n].id.label = "Orry_House";
locations[n].image = "loading\inside\largehouse01.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\largehouse01";
locations[n].models.always.largehouse01 = "largehouse01";
locations[n].models.always.largehouse01.level = 65538;
locations[n].models.always.locators = "largehouse01_lPLQ5Bermudes";
Locations[n].models.always.largehouse01windows = "largehouse01_windows";
Locations[n].models.always.largehouse01windows.tech = "LocationWindows";
locations[n].models.always.largehouse01windows.level = 65539;
Locations[n].models.back = "..\back\inside_back_";
//Day
Locations[n].models.day.largehouse01rand= "largehouse01_rand";
locations[n].models.day.charactersPatch = "largehouse01_patch";
//Night
locations[n].models.night.charactersPatch = "largehouse01_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "houseS1";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
locations[n].reload.l2.name = "reload2";
locations[n].reload.l2.go = "CommonRoom_MH5";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "Room";
n = n + 1;
locations[n].id = "Bermudes_Hut1";
locations[n].id.label = "House";
locations[n].image = "inside\largehouse01.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\Hut1";
locations[n].models.always.locators = "Hut1_locators";
locations[n].models.always.hut1 = "Hut1";
//Day
locations[n].models.day.charactersPatch = "Hut1_patch";
//Night
locations[n].models.night.charactersPatch = "Hut1_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "houseH1";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
n = n + 1;
locations[n].id = "Bermudes_Hut2";
locations[n].id.label = "house";
Locations[n].image = "Inside_MediumHouse2.tga";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
Locations[n].filespath.models = "locations\Inside\MediumHouse2";
Locations[n].models.always.locators = "MH02_l";
Locations[n].models.always.house = "MH02";
Locations[n].models.always.window = "MH02_w";
Locations[n].models.always.window.tech = "LocationWindows";
Locations[n].models.always.window.level = 50;
Locations[n].models.back = "back\smumh2_";
//Day
Locations[n].models.day.charactersPatch = "MH02_p";
//Night
Locations[n].models.night.charactersPatch = "MH02_p";
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_town";
locations[n].reload.l1.emerge = "houseSp1";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "#stown_name#";
n = n +1;
locations[n].id = "Bermudes_Hut3";
locations[n].id.label = "house";
Locations[n].image = "Inside_MediumHouse.tga";
//Town sack
locations[n].townsack = "Bermudes";
locations[n].lockWeather = "Inside";
//Sound
locations[n].type = "house";
locations[n].fastreload = "Bermudes";
locations[n].island = "Bermudes";
//Models
//Always
Locations[n].filespath.models = "locations\Inside\MediumHouse";
Locations[n].models.always.locators = "MH_l";
Locations[n].models.always.house = "MH";
Locations[n].models.always.window = "MH_w";
Locations[n].models.always.window.tech = "LocationWindows";
Locations[n].models.always.window.level = 50;
//Day
Locations[n].models.day.charactersPatch = "MH_p";
//Night
Locations[n].models.night.charactersPatch = "MH_p";
//Environment
Locations[n].environment.weather = "false";
Locations[n].environment.sea = "false";
Locations[n].models.back = "back\smumh_";
//Reload map
Locations[n].reload.l1.name = "reload1";
Locations[n].reload.l1.go = "Bermudes_town";
Locations[n].reload.l1.emerge = "under";
Locations[n].reload.l1.autoreload = "0";
Locations[n].reload.l1.label = "#stown_name#.";
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Подземелье Бермудов
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_Dungeon";
locations[n].id.label = "Dungeon";
locations[n].image = "loading\inside\dungeon.tga.tx";
//Town sack
locations[n].townsack = "Bermudes";
//Sound
locations[n].type = "Dungeon";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\DungeonVault1";
locations[n].models.always.DungeonVault1 = "DungeonVault1";
locations[n].models.always.InquisitionDungeonVault1Fonars = "DungeonVault1_fonars";
locations[n].models.always.locators = "DungeonVault1_locators";
locations[n].locators_radius.item.duhi1 = 1.3;
//Day
locations[n].models.day.charactersPatch = "DungeonVault1_patch";
//Night
locations[n].models.night.charactersPatch = "DungeonVault1_patch";
//Environment
locations[n].environment.weather = "true";
Locations[n].lockWeather = "Inside";
Locations[n].QuestlockWeather = "23 Hour";
locations[n].environment.sea = "false";
locations[n].environment.weather.rain = false;
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_Shipyard";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_Shore_1";
locations[n].reload.l2.emerge = "reload2";
locations[n].reload.l2.autoreload = "1";
locations[n].reload.l2.label = "Bermudes_Shore_1";
locations[n].locators_radius.reload.reload2_back = 1.5;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Пляж 3  (два выхода)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_Shore_1";
locations[n].id.label = "Bermudes_Shore_1";
locations[n].worldmap = "Bermudes_Shore_1";
locations[n].image = "loading\outside\harbor3.tga.tx";
//Sound
locations[n].type = "seashore";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\Outside\Shore04";
Locations[n].models.always.shore04 = "shore04";
Locations[n].models.always.shore04.foam = "1";
locations[n].models.always.shore04.sea_reflection = 1;
Locations[n].models.always.shore04seabed = "shore04_sb";
Locations[n].models.always.shore04seabed.foam = "1";
Locations[n].models.always.locators = "shore04_locators";
Locations[n].models.always.grassPatch = "shore04_grass";
Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
Locations[n].models.always.l1 = "plan1";
Locations[n].models.always.l1.level = 9;
Locations[n].models.always.l1.tech = "LocationModelBlend";
Locations[n].models.always.l2 = "plan2";
Locations[n].models.always.l2.level = 8;
Locations[n].models.always.l2.tech = "LocationModelBlend";
Locations[n].models.always.l3 = "plan3";
Locations[n].models.always.l3.level = 7;
Locations[n].models.always.l3.tech = "LocationModelBlend";
//Day
locations[n].models.day.charactersPatch = "shore04_patch";
//Night
locations[n].models.night.charactersPatch = "shore04_patch";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "true";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_jungle_01";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "1";
locations[n].reload.l1.label = "Jungle";
locations[n].locators_radius.reload.reload1_back = 1;
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_Dungeon";
locations[n].reload.l2.emerge = "reload2";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "Dungeon";
locations[n].locators_radius.reload.reload2_back = 1.5;
locations[n].reload.l3.name = "boat";
locations[n].reload.l3.go = "Bermudes";
locations[n].reload.l3.emerge = "reload_2";
locations[n].reload.l3.autoreload = "0";
locations[n].reload.l3.label = "Sea";
locations[n].locators_radius.reload.boat = 9.0;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Джунгли
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_jungle_01";
locations[n].id.label = "Jungle";
locations[n].image = "loading\outside\jungle.tga.tx";
//Sound
locations[n].type = "jungle";
locations[n].island = "Bermudes";
//Models
//Always
Locations[n].filespath.models = "locations\Outside\jungle_8";
Locations[n].models.always.jungle = "jungle08";
Locations[n].models.always.locators = "jungle08_l";
Locations[n].models.always.grassPatch = "JUNGLE08_g";
Locations[n].models.always.l1 = "plan_1";
Locations[n].models.always.l1.level = 9;
Locations[n].models.always.l1.tech = "LocationModelBlend";
Locations[n].models.always.l2 = "plan_2";
Locations[n].models.always.l2.level = 8;
Locations[n].models.always.l2.tech = "LocationModelBlend";
Locations[n].models.always.l3 = "plan_3";
Locations[n].models.always.l3.level = 7;
Locations[n].models.always.l3.tech = "LocationModelBlend";
//Day
Locations[n].models.day.charactersPatch = "jungle08_p";
//Night
Locations[n].models.night.charactersPatch = "jungle08_p";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_jungle_02";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "1";
locations[n].reload.l1.label = "Jungle";
locations[n].locators_radius.reload.reload1_back = 2.0;
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_Shore_1";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "1";
locations[n].reload.l2.label = "Bermudes_Shore_1";
locations[n].locators_radius.reload.reload2_back = 2.0;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Вход в пещеру
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_jungle_02";
locations[n].id.label = "Cave entrance";
locations[n].image = "loading\outside\jungle2.tga.tx";
//Sound
locations[n].type = "jungle";
locations[n].island = "Bermudes";
//Models
//Always
Locations[n].filespath.models = "locations\Outside\Cave Entrance";
Locations[n].models.always.locators = "Cave_l";
Locations[n].models.always.cave = "Cave";
Locations[n].models.always.grassPatch = "CAVE_g";
Locations[n].models.always.l1 = "cave_b01";
Locations[n].models.always.l1.level = 9;
Locations[n].models.always.l1.tech = "LocationModelBlend";
Locations[n].models.always.l2 = "cave_b02";
Locations[n].models.always.l2.level = 8;
Locations[n].models.always.l2.tech = "LocationModelBlend";
Locations[n].models.always.l3 = "cave_b03";
Locations[n].models.always.l3.level = 7;
Locations[n].models.always.l3.tech = "LocationModelBlend";
Locations[n].models.always.l4 = "cave_b04";
Locations[n].models.always.l4.level = 6;
Locations[n].models.always.l4.tech = "LocationModelBlend";
//Day
Locations[n].models.day.charactersPatch = "Cave_p";
//Night
Locations[n].models.night.charactersPatch = "Cave_p";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "false";
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_Cavern";
locations[n].reload.l1.emerge = "reload1";
locations[n].reload.l1.autoreload = "0";
locations[n].reload.l1.label = "Cave";
locations[n].locators_radius.reload.reload1_back = 1.3;
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_jungle_01";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "1";
locations[n].reload.l2.label = "Jungle";
locations[n].locators_radius.reload.reload2_back = 2.0;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Сковозная пещера
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_Cavern";
locations[n].id.label = "Cave";
locations[n].image = "loading\inside\cave.tga.tx";
//Sound
locations[n].type = "cave";
locations[n].island = "Bermudes";
//Models
//Always
locations[n].filespath.models = "locations\inside\cavernLow1";
locations[n].models.always.cavernLow1 = "cavernLow1";
locations[n].models.always.cavernLow1Lamps = "cavernLow1_lamps";
locations[n].models.always.cavernLow1Crystals = "cavernLow1_crystals";
locations[n].models.always.cavernLow1Crystals.tech = "EnvironmentShader";
locations[n].models.always.cavernLow1Crystals.reflection = 0.25;
locations[n].models.always.Waterfall = "water";
locations[n].models.always.Waterfall.uvslide.v0 = 0.0;
locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
locations[n].models.always.Waterfall.tech = "LocationWaterFall";
locations[n].models.always.Waterfall.level = 51;
locations[n].models.always.Cfall = "cfall";
locations[n].models.always.Cfall.uvslide.v0 = 0.3;
locations[n].models.always.Cfall.uvslide.v1 = 0.0;
locations[n].models.always.Cfall.tech = "LocationWaterFall";
locations[n].models.always.Cfall.level = 50;
locations[n].models.always.locators = "cavernLow1_locators";
//Day
locations[n].models.day.charactersPatch = "cavernLow1_patch";
//Night
locations[n].models.night.charactersPatch = "cavernLow1_patch";
//Environment
locations[n].environment.weather = "true";
Locations[n].lockWeather = "Inside";
Locations[n].QuestlockWeather = "23 Hour";
locations[n].environment.sea = "false";
locations[n].environment.weather.rain = false;
//Reload map
locations[n].reload.l1.name = "reload1_back";
locations[n].reload.l1.go = "Bermudes_jungle_02";
locations[n].reload.l1.emerge = "reload1";
locations[n].reload.l1.autoreload = "1";
locations[n].reload.l2.name = "reload2_back";
locations[n].reload.l2.go = "Bermudes_Shore_2";
locations[n].reload.l2.emerge = "reload1";
locations[n].reload.l2.autoreload = "1";
locations[n].locators_radius.reload.reload2_back = 2;
locations[n].locators_radius.quest.BlueBird = 1.0;
n = n + 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Бухта с кораблем
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
locations[n].id = "Bermudes_Shore_2";
locations[n].id.label = "Bermudes_Shore_2";
locations[n].image = "loading\outside\harbor3.tga.tx";
locations[n].worldmap = "Bermudes_Shore_2";
//Sound
locations[n].type = "seashore";
locations[n].island = "Bermudes";
//Models
//Always
Locations[n].filespath.models = "locations\Outside\Shore_ship";
Locations[n].models.always.jungle = "ShoreShip";
Locations[n].models.always.jungle.foam = "1";
Locations[n].models.always.locators = "ShoreShip_l";
Locations[n].models.always.grassPatch = "ShoreShip_g";
Locations[n].models.always.seabed = "ShoreShip_sb";
Locations[n].models.always.seabed.foam = "1";
Locations[n].models.always.l1 = "plan_1";
Locations[n].models.always.l1.level = 9;
Locations[n].models.always.l1.tech = "LocationModelBlend";
Locations[n].models.always.l2 = "plan_2";
Locations[n].models.always.l2.level = 8;
Locations[n].models.always.l2.tech = "LocationModelBlend";
Locations[n].models.always.l3 = "plan_3";
Locations[n].models.always.l3.level = 7;
Locations[n].models.always.l3.tech = "LocationModelBlend";
//Day
Locations[n].models.day.charactersPatch = "ShoreShip_p";
//Night
Locations[n].models.night.charactersPatch = "ShoreShip_p";
//Environment
locations[n].environment.weather = "true";
locations[n].environment.sea = "true";
//Reload map
locations[n].reload.l1.name = "reload1";
locations[n].reload.l1.go = "Bermudes_Cavern";
locations[n].reload.l1.emerge = "reload2";
locations[n].reload.l1.autoreload = "1";
locations[n].reload.l1.label = "Cave";
locations[n].locators_radius.reload.reload1 = 3;
locations[n].reload.l2.name = "boat";
locations[n].reload.l2.go = "Bermudes";
locations[n].reload.l2.emerge = "reload_3";
locations[n].reload.l2.autoreload = "0";
locations[n].reload.l2.label = "Sea";
locations[n].locators_radius.reload.boat = 9.0;
n = n + 1;
}