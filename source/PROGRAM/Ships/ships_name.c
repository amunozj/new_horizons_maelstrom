void InitRandomShipsNames()
{
	// Spain names
	int n = 0;
	n = AddStr2Array(&sRndShpSpName, n, "Alfonso X,Am�rica,Aquil�n,Andaluz,Ave de Gracia,Aventura,�frica,�guila,Amazona,Aurora,Anf�trite");		//some spanish ship names spell-checked by KAM
	n = AddStr2Array(&sRndShpSpName, n, "�ngel de la Guarda,Anunciaci�n,Antilla,Argonauta,Arrogante,Asia,Astrea,Astuto,Asunci�n,Atlante,Atrevida,Bahama,Baleares,B�rbara,Brillante");
	n = AddStr2Array(&sRndShpSpName, n, "Bizarro,Bravo,Catal�n,Canarias,C�ntabro,Carmen,Constante,Carlota,Carmelita,Castilla,Cazador,Ceres,Cierva,Clara");
	n = AddStr2Array(&sRndShpSpName, n, "Concepci�n,Calipso,Conquistador,Caim�n,Corso,San Cosme,Cagafuego,Cuervo,D�dalo,Descubierta,Delf�n,Diana,Diligencia,Don Antonio");
	n = AddStr2Array(&sRndShpSpName, n, "Estrella del Mar,Esmeralda,Espa�a,Esperanza,Europa,Extremadura,Fama,Feliz,F�nix,Firme,Flecha,Flora");
	n = AddStr2Array(&sRndShpSpName, n, "Formidable,Fuerte,Gallardo,Galgo,Galicia,Gamo,Gertrudis,Guarnizo,Glorioso,Guerrera,Guipuzcoana,Gitano");
	n = AddStr2Array(&sRndShpSpName, n, "Halc�n,Hermenegildo,Herm�one,Infanta,Isla de Cuba,Ifigenia,Intr�pido,Isabela,Jaime I,Jes�s Mar�a y Jos�,Invencible,Juno,Liebre,Ligera,Lebrel");
	n = AddStr2Array(&sRndShpSpName, n, "Magn�nima,Mahonesa,Mar�a Sant�sima,Mercurio,Matilda,Medea,Matamoros,Mercedes,Mallorqu�n,Minerva,Mi�o");
	n = AddStr2Array(&sRndShpSpName, n, "Monarca,Monta��s,Murciana,Nuestra Se�ora del Carmen,Natividad,Navarra,Navas de Tolosa,Neptuno,Ninfa,Numancia,Oriente,Urquijo,Palas,P�xaro,Paz,Paloma");
	n = AddStr2Array(&sRndShpSpName, n, "Perla,Pinta,Princesa,Pr�ncipe de Asturias,Raposa,Rayo,Real Familia,Ni�a,Reina Mar�a Luisa,Reina del Mar,Reina de Cuba,Reina");
	n = AddStr2Array(&sRndShpSpName, n, "Resoluci�n,Rosario,Sabina,San Antonio,San August�n,Santander,Santa B�rbara,San Bernardo,San Blas,San Bruno");
	n = AddStr2Array(&sRndShpSpName, n, "San Carlos,San D�maso,San Eugenio,San Felipe,San Ferm�n,San Fernando,San Francisco,San Mart�n,Sant�sima Madre");
	n = AddStr2Array(&sRndShpSpName, n, "San Fulgencio,San Gabriel,San Genaro,San Gil,San Ildefonso,San Isidro,San Joaqu�n,Sant�sima Trinidad");
	n = AddStr2Array(&sRndShpSpName, n, "San Jos�,Sant�simo Sacramento,San Juan Bautista,San Juan Nepomuceno,Sagunto,San Juli�n,San Justo");
	n = AddStr2Array(&sRndShpSpName, n, "Septentri�n,San Leandro,San Le�n,San Lino,San Lorenzo,San Nicol�s,San Pablo,San Pascual");
	n = AddStr2Array(&sRndShpSpName, n, "San Pedro,San Pedro Ap�stal,San P�o,San Rafael,San Ram�n,San Sebasti�n");
	n = AddStr2Array(&sRndShpSpName, n, "San Vicente,San Isidro,San Felipe,Santa �gueda,Santa Ana,Santa Br�gida,Santa Catalina");
	n = AddStr2Array(&sRndShpSpName, n, "Santa Casilda,Santa Cecilia,Santa Clara,Santa Dorotea,Santa Elena,Santa Escol�stica");
	n = AddStr2Array(&sRndShpSpName, n, "Santa Florentina,Santa Gertrudis,Santa Isabel,Santa Leocadia,Santa Luc�a,Santa Margarita");
	n = AddStr2Array(&sRndShpSpName, n, "Santa Mar�a,Santa Mar�a Magdalena,Santa Matilde,Santa Perpetua,Santa Raquel,Santa Rita");
	n = AddStr2Array(&sRndShpSpName, n, "Santa Rosa,Santa Rosal�a,Santa Rufina,Santa Sabina,Santa Eulalia,Santa Teresa,Tigre,San Telmo");
	n = AddStr2Array(&sRndShpSpName, n, "Sacramento,Santiago,Sirena,Siroco,Soberana,T�rtaro,Temerario,Terrible,Tetis,Tonina,Tramontana,Triunfante,Trucha,Valiente,Valerosa");
	n = AddStr2Array(&sRndShpSpName, n, "Velasco,Veloz,Vencedora,Venganza,Venus,Vencejo,Volador,Vitoria,Viva,Vizcaya,Viento,Zaragoza,");
	if(GetCurrentPeriod() >= PERIOD_THE_SPANISH_MAIN)
	{
		n = AddStr2Array(&sRndShpSpName, n, "Col�n,Cuzco,Don Juan de Austria,Emperador Carlos V,Lepanto,Lime�o,Mejicana,Nueva Espa�a,Peruano,R�o de la Plata,Villa de Madrid");
	}
	if(GetCurrentPeriod() >= PERIOD_COLONIAL_POWERS)
	{
		n = AddStr2Array(&sRndShpSpName, n, "Almansa");
	}
	if(GetCurrentPeriod() >= PERIOD_REVOLUTIONS)
	{
		n = AddStr2Array(&sRndShpSpName, n, "Blas de Lezo");
	}

	// England names
	n = 0;
	n = AddStr2Array(&sRndShpEnName, n, "Acasta,Achar,Achille,Acorn,Active,Actoeon,Acute,Adamant,Adonis,Advice,Aeolus,Africa,Africaine,Agamemnon,Agincourt,Agressor,Aigle");
	n = AddStr2Array(&sRndShpEnName, n, "Aildreda,Alacrity,Alarm,Alban,Albicore,Albion,Alceste,Alcide,Alcmene,Alexander,Alfred,Algerian,Allemaar,Alligator,Alonso,Amaranthe");
	n = AddStr2Array(&sRndShpEnName, n, "Amazon,Amelia,Amethyst,Amphion,Amphitrite,Anacreon,Andromeda,Angel,Antelope,Apelles,Apollo,Aquilon,Arab,Ardent,Argo,Argonaute,Ariadne");
	n = AddStr2Array(&sRndShpEnName, n, "Ariel,Ark Royal,Armada,Arrogant,Arrow,Artoise,Asia,Assistance,Assurance,Astrea,Atalanta,Athenienne,Atlas,Audacious,Aurora,Avenger,Avon,Bacchante,Bacchus");
	n = AddStr2Array(&sRndShpEnName, n, "Badger,Barfleur,Barham,Barossa,Basilisk,Beagle,Bedford,Belleisle,Bellerophon,Bellona,Benbow,Berkeley,Berwick,Black Prince,Blake,Blanche,Bold");
	n = AddStr2Array(&sRndShpEnName, n, "Bonneta,Leyte Brave,Brazen,Brilliant,Brisk,Bristol,Britannia,Briton,Brothers,Bruizer,Bucephalus,Bulldog,Bustard,Butler,Caesar,Calcutta,Caledonia,Calypso");
	n = AddStr2Array(&sRndShpEnName, n, "Cambridge,Camilla,Canopus,Carnatic,Caroline,Castor,Catherine,Censor,Centaur,Centurion,Cerberus,Ceres,Champion,Charger,Charlotte,Charon,Cherokee");
	n = AddStr2Array(&sRndShpEnName, n, "Cherub,Circe,Clementine,Cleopatra,Cockatrice,Colossus,Comet,Confounder,Conqueror,Conquest,Courageous,Cordelia,Cornelia,Cossack,Courier,Cracker");
	n = AddStr2Array(&sRndShpEnName, n, "Creole,Crescent,Cressy,Crocodile,Crown,Cyane,Cyclop,Cygnet,Daedalus,Danae,Dannemark,Daphne,Daring,Dashe,Dashield,Decoy,Defender,Defiance,Delight,Desiree");
	n = AddStr2Array(&sRndShpEnName, n, "Desperate,Diadem,Diamond,Diana,Dictator,Dido,Diligente,Diomede,Director,Discovery,Dolphin,Doris,Dragon,Drake,Dreadnaught,Driver,Dromedary,Druid");
	n = AddStr2Array(&sRndShpEnName, n, "Dryad,Dublin,Duchess,Duke of York,Duncan,Eagle,Echo,Eclipse,Edgar,Egmont,Egyptienne,Elephant,Elizabeth,Emerald,Enchantress,Encounter,Endymion,Enterprise,Entreprenant");
	n = AddStr2Array(&sRndShpEnName, n, "Escort,Ethalion,Europa,Eurotas,Euryalus,Eurydice,Excellent,Exmouth,Expedition,Experiment,Fairy,Falcon,Fame,Favorite,Fawn,Ferret,Firm,Flirt,Flora,Fly,Formidable");
	n = AddStr2Array(&sRndShpEnName, n, "Fortitude,Fortune,Fox,Foxhound,Frolic,Fury,Galatea,Gallant,Gannet,Ganymede,Garland,Gipsy,Gladiator,Glasgow,Glory,Goldfinch,Goliath");
	n = AddStr2Array(&sRndShpEnName, n, "Goodly,Grampus,Grasshopper,Greyhound,Halifax,Hannah-Rose,Hannibal,Harpy,Hasty,Haughty,Havoc,Hawk,Hazard,Hebe,Hector,Helena,Hercules,Hermione");
	n = AddStr2Array(&sRndShpEnName, n, "Hero,Heroine,Heron,Hibernia,Hind,Adelaide,Ajax,Bermuda,Cormorant,Dauntless,Dreadnought,Erebus,Fencer,Furious,Mary Rose, Golden Lion,Devonshire");
	n = AddStr2Array(&sRndShpEnName, n, "Glorious,Hermes,Highlander,Nairana,Phaeton,Superb,Tiger,Valiant");
	n = AddStr2Array(&sRndShpEnName, n, "Horatio,Hostile,Hound,Hussar,Hyaena,Hydra,Hyperion,Illustrious,Implacable,Impregnable,Inconstant,Inflexible,Intrepid,Invincible");
	n = AddStr2Array(&sRndShpEnName, n, "Iphigenia,Iris,Irresistible,Isis,Jason,Javelin,Juno,Jupiter,Juste,Kangaroo,Katherine,Kent,Jackal,Jaguar,Kite,Lancaster,Lapwing,Latona,Lavinia,Leda,Legion,Leonidas,Leopard,Levant,Leviathan");
	n = AddStr2Array(&sRndShpEnName, n, "Liberty,Lightning,Lion,Little Sally,Lively,Lizard,London,Lydia,Lynx,Lyra,Macedonian,Magnanime,Magnificent,Majestic,Mariner,Marital,Mars,Martin,Mary");
	n = AddStr2Array(&sRndShpEnName, n, "Medina,Medusa,Medway,Melampus,Meleoger,Melpomene,Mercury,Merlin,Mermaid,Meteor,Minerva,Minotaur,Minstrel,Monarch,Mosquito,Myrmidon,Mullet,Mutine,Naid,Narcissus");
	n = AddStr2Array(&sRndShpEnName, n, "Nautilus,Nemesis,Neptune,Nereus,Nimble,Nimrod,Nonsuch,Nymphe,Obedient,Ocean,Olympia,Opossum,Orestes,Orion,Otter,Paladin,Pallas,Pandora,Partridge,Pathfinder,Paulette,Peacock,Pearl");
	n = AddStr2Array(&sRndShpEnName, n, "Pegasus,Pelican,Penelope,Perseus,Perseverance,Phoebe,Phoenix,Phoeton,Piercer,Pilot,Pincher,Pioneer,Plover,Plumper,Pluto,Polyphemus,Powerful,Prince of Wales,Princess");
	n = AddStr2Array(&sRndShpEnName, n, "Prompt,Proserpine,Protector,Prothee,Prudent,Psyche,Pygmy,Pyramus,Racehorse,Rainbow,Ramillies,Reason,Reasonable,Ranger,Rattlesnake,Ready,Rebuff,Recovery,Redbreast");
	n = AddStr2Array(&sRndShpEnName, n, "Redpole,Regulus,Reindeer,Renown,Repulse,Resistance,Resolution,Resource,Retaliation,Retribution,Reunion,Revenge,Revolutionnaire,Romney,Romulus,Rose,Rover,Royalist");
	n = AddStr2Array(&sRndShpEnName, n, "Royal Oak,Royal Sovereign,Ruby,Sabrina,Sandwich,Saturn,Savage,Scamander,Sceptre,Scipio,Scorcher,Scorpion,Scourge,Scout,Seahorse,Semiramis,Serapis,Serpent,Shark,Shearwater");
	n = AddStr2Array(&sRndShpEnName, n, "Sirius,Snake,Solitaire,Spartan,Speedwell,Speedy,Spencer,Sphynx,Spider,Spitfire,Sprightly,Spy,Squirrel,Stag,Standard,Starling,Sturgeon,Success,Sultan,Surprise,Susan");
	n = AddStr2Array(&sRndShpEnName, n, "Swaggerer,Swallow,Swan,Swift,Swiftsure,Swordfish,Sybille,Sylph,Syren,Talisman,Tartar,Teaser,Telemachus,Tempest,Terpsichore,Terrapin,Terrible,Thais,Thames,Theseus,Thetis,Thistle,Thorn,Thunderbolt");
	n = AddStr2Array(&sRndShpEnName, n, "Tickler,Tigress,Traveller,Tremendous,Trepassy,Trial,Tribune,Trident,Trimmer,Trinidad,Triton,Triumph,Trooper,Trusty,Turbulent,Turpin,Ulysses,Undaunted,Unicorn,Union,Unite,Urgent,Vanguard,Venerable");
	n = AddStr2Array(&sRndShpEnName, n, "Vengenance,Venus,Vesta,Vestal,Veteran,Victor,Victory,Victorious,Vigilant,Vindictive,Viper,Vixen,Voyager,Vulture,Warrior,Warspite,Wasp,Wild Swan,Wren,Wolverine,Wrangler,Yarmouth,Zealous,Zebra,Zulu");
	if(GetCurrentPeriod() >= PERIOD_THE_SPANISH_MAIN)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Grenville,Queen Elizabeth,Raleigh,Sir Francis Drake");
	}
	if(GetCurrentPeriod() >= PERIOD_GOLDEN_AGE_OF_PIRACY)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Blenheim,King George");
	}
	if(GetCurrentPeriod() >= PERIOD_COLONIAL_POWERS)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Anson,General Monck");
	}
	if(GetCurrentPeriod() == PERIOD_NAPOLEONIC)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Cornwallis,Hood,Rodney");
	}

	// France names
	n = 0;
	n = AddStr2Array(&sRndShpFrName, n, "Abeille,Achates,Achille,Actif,Aelcon,Africaine,Agricole,Aigle,Alceste,Alcide,Alerte,Alexandre,Algeciras,Alouette,Amaranthe,Amazone,Ambuscade,Am�rique,Andromaque,Annibal");		//some french ship names spell-checked by KAM
	n = AddStr2Array(&sRndShpFrName, n, "Antelope,Apollon,Aquilon,Ardente,Artheuse,Argonaute,Ariel,Art�mise,Art�sien,Astr�e,Atalante,Atlas,Audocieux,Auguste,Aurore,Babet,Badine,Baionnaise,Belette,Belleisle,Bellone");
	n = AddStr2Array(&sRndShpFrName, n, "Berceau,Berwick,Bestale,Betsey,Bizarre,Blanche,Bienvenue,Blonde,Bolontaire,Bonne Citoyenne,Bor�e,Boudeuse,Boudissant,Bourbonnaise,Bourgogne,Brave,Bravoure,Breslaw,Brillante");
	n = AddStr2Array(&sRndShpFrName, n, "Brune,Brutus,Bucentaure,Caire,Calliope,Calliope,Calypso,Capricieuse,Carmagnole,Caroline,Cartagenoise,Cassard,Castor,Censeur,Centaure,Ceres,Chameau,Charente,Ch�rie,Chiffone");
	n = AddStr2Array(&sRndShpFrName, n, "Cisalpine,Citoyenne,Cleopatre,Clorinde,Cocade,Concorde,Confiance,Confiante,Conqu�rante,Consolante,Constance,Constitution,Convention");
	n = AddStr2Array(&sRndShpFrName, n, "Coquille,Cormagnole,Corn�lie,Cornette,Courier,C�te d'Or,Courageuse,Courier,Couronne,Cr�tin,Curleuse,Cyb�le,Danae,Dasaix,Decade,Decuise,Decuise,Dedaigneuse,Desire");
	n = AddStr2Array(&sRndShpFrName, n, "Desir�e,Destin,Diademe,Diane,Didon,Diligente,Dix Ao�t,Droits de l'homme,Droits du Peuple,Dryade,Duc de Bourgogne,Duguai Trouin,Dulyce,Duquesne,Durance,Duras,�chaude,�claire,�gyptienne");
	n = AddStr2Array(&sRndShpFrName, n, "Electra,�lisabeth,�liza,Embroie,�meraude,Emulus,Enchantrice,Engageante,Entreprenante,Eole,Epervier,Esp�rance,Espion,�toile,�veille,Fant�me,Fauvette,F�e,F�licit�,Fendant,Fid�le,Filibustier");
	n = AddStr2Array(&sRndShpFrName, n, "Fine,Flamande,Fl�che,Fleuron,Flore,Formidable,Forte,Fortun�e,Foudrayante,Fougueuse,Franklin,Fraternit�,Friponne,Furet,Furieuse,Galath�e,Gasparin,G�n�reuse,Gentille,Gloire,Glorieuse,Gracieuse");
	n = AddStr2Array(&sRndShpFrName, n, "Grande,Guadaloupe,Guerrier,Guillaume Tell,Hannibal,Hardie,Hassard,Hector,Hehe,Hel�ne,Hercule,Hermione,H�ros,Heureux,Hirondelle,Hoche,Harmonie,Heureuse,Illustre,Impatiente,Immortalit�,Imp�riale");
	n = AddStr2Array(&sRndShpFrName, n, "Imperieuse,Imp�tueuse,Inconnue,Inconstante,Incorruptible,Indienne,Indivisible,Indomptable,Insolente,Insurgente,Intr�pide,Invincible,Iphig�nie,Iriste,Jacobine,Jean Bart,Jena,Junon,Jupiter,Juste,Justice");
	n = AddStr2Array(&sRndShpFrName, n, "Justine,Latone,L�g�re,Leopard,L�vrier,Libert�,Libre,Lion,Loire,L'Orient,Lutine,Magnanime,Magnifique,Maida,Malicieuse,Marat,Marengo,Marseillaise,Marte,Med�e,M�duse,Melpomene,Mercure");
	n = AddStr2Array(&sRndShpFrName, n, "Mignonne,Minerve,Minotaure,Modeste,Mont Blanc,Montagne,Montr�al,Moselle,Mucius,Mulet,Musette,Mutine,Nemesis,Neptune,Nereide,Neuf Thermidor,Nieman,Nymphe,Oc�an,Orient,Orion,Pallas,Palmier");
	n = AddStr2Array(&sRndShpFrName, n, "Papillon,Patriote,Paulette,Pegase,Pelletier,Pensee,Perdrix,Perle,Perte,Petite Aurore,Phocion,Pique,Pluton,Pomone,Pompee,Poulette,Precieuse,Preneuse,Prevoyante,Prompte,Proselyte,Proserpine");
	n = AddStr2Array(&sRndShpFrName, n, "Protecteuse,Prudente,Puissante,Railleuse,Railleuse,Rapide,Rebecca,Recluse,Redoutable,R�fl�chie,Regener�e,Renomm�e,Reprisal,Requin,R�sistance,R�solue,R�solution,R�union,Revanche,Revenge,Richelieu,Rivoli");
	n = AddStr2Array(&sRndShpFrName, n, "Robuste,Romaine,Rousseau,Royal C�sar,Ruse,Sagesse,Sainte Antoine,Salamine,Sardine,Scaevala,Sceptre,Scipion,Seduisante,Seine,Semillante,Sensible,Serpente,S�v�re,Sincere,Singe,Spartiate,Sphinx");
	n = AddStr2Array(&sRndShpFrName, n, "St. Esprit,St. Michel,Suffisante,Suffren,Suitane,Sultana,Superbe,Sup�rieure,Surveillante,Swiftsure,Sybille,Syrene,Tactique,Tamise,Tapageuse,Tapaze,Tartouffe,Terrible,Thetis,Tigresse,Timoleon");
	n = AddStr2Array(&sRndShpFrName, n, "Tonnante,Tonn�re,Tortue,Tourtourelle,Tourville,Trajan,Trampeuse,Tribune,Trident,Triomphant,Tyrannicide,Unit�,Uranie,Vaillante,Varsovie,Vend�e,Vengeance,Vengeur,Venturer");
	n = AddStr2Array(&sRndShpFrName, n, "Venus,Vertu,Vestale,Vesuve,Victoire,Victorieuse,Vim�ria,Virginie,Virtu,Volcan,Wagram,Wattignies,Zephyr");
	if(GetCurrentPeriod() == PERIOD_NAPOLEONIC)
	{
		n = AddStr2Array(&sRndShpFrName, n, "Commerce de Bordeaux,Commerce de Marseilles,Trente et Un Mai,Tricolore");
	}
	else
	{
		n = AddStr2Array(&sRndShpFrName, n, "Dauphin Royal,Majest�");
	}

	// Pirate names
	n = 0;
	n = AddStr2Array(&sRndShpPiName, n, "Adventure,Adventure Galley,Adventure Prize,Bachelors Delight,Black Joke,Blanco,Blessing,Bravo,Concorde,Itchen,Jed,Ostergo,Overijssell,Pluto,Prins Frederik,Prins Maurits,Revolutie,Rotterdam,Utrecht,Verwachting,Wassenaar,Westergo,Westfriesland");		//some pirate ship names spell-checked by KAM
	n = AddStr2Array(&sRndShpPiName, n, "Zeeland,Zevenwalder,Zevenwolder,Zuid Beveland,Nassau,Octopus,Princesse Louise,Mackerel,Manta,Medregal,Menhaden,Mero,Ohio,Virginia,Nebraska,Georgia");
	n = AddStr2Array(&sRndShpPiName, n, "Papillon,Patriote,Royal Fortune,Paulette,Pegase,Pelletier,Pens�e,Golden Hind,Perdrix,Perle,Perte,Petite Aurore,Phocion,Pique,Cassandra,Childhood");
	n = AddStr2Array(&sRndShpPiName, n, "Pluton,Pomone,Pomp�e,Poulette,Precieuse,Preneuse,Prevoyante,Prompte,Pros�lyte,Proserpine,Queenfish,Sirius,Snake,Solitaire,Spartan,Speedwell,Speedy,Spencer,Sphinx,Spider,Spitfire");
	n = AddStr2Array(&sRndShpPiName, n, "Sprightly,Spy,Squirrel,Stag,Standard,Starling,Success,Sultan,Sumter,Surprise,Susan,Tarantula,Velasco,Velosa,Vencedor,Venganza,Venus,Vincejo,Vivo,Voader,Vermont");
	n = AddStr2Array(&sRndShpPiName, n, "Cour Valant,Delight,Delivery,Desire,Fancy,Flying Dragon,Flying Horse,Flying King,Gift,Good Fortune,Mayflower,Night Rambler,Rising Sun,Sea King,Sudden Death,Whydah,Snap Dragon");
	n = AddStr2Array(&sRndShpPiName, n, "La Mort,La Faucheuse,Enfer,Immortel,Le Terrible,Le Sans Piti�,�pop�e,�pervier,La Frayeur,�pilogue,Le Satan,Le Diable,Insoumis,Le Mort Vivant,Angoisse,Le D�sinvolte,Le Larcin");
	n = AddStr2Array(&sRndShpPiName, n, "Devil,Demon,Sea Devil,Sea Demon,Ocean Devil,Ocean Demon,Merciless,Plaguebringer,Black Queen,Black King,Red Queen,Fishking,Hunter,Avenger,Blackdeath,Infection");
	n = AddStr2Array(&sRndShpPiName, n, "Seawitch,Grey Witch,Red Witch,Black Witch,Black Knight,Nightstalker,Stealthy,Sneaky,Deathbringer,Golden King,Golden Queen,Hawk,Seawolf,Blackshark,Red Shark,Nightwolf,Wolf,Predator");
	n = AddStr2Array(&sRndShpPiName, n, "Old Hag,Ocean Hag,Seagiant,Black Giant,Deathwish,Glorious,Infamous,Bad luck,Revenge,Goldseeker,Ruby,Emerald,Sapphire,Diamond,Black Diamond,Red Blood,Bloodred");
	n = AddStr2Array(&sRndShpPiName, n, "Vampire,Nightlord,Nightlady,Empty Pockets,Forsaken,Topaz,Bloodred Garnet,Lucky,Fortunate,Abyss,Hellraiser,Headless Rider,Ghost,Misty,Poisonous,Snakebite,Venom,Lupus");
	n = AddStr2Array(&sRndShpPiName, n, "Sinner,Heretic,Hand of Midas,Troublemaker,Trouble,Swift Danger,Dangerous,Silent Thief,Intruder,Veni Vidi Vici,Media Nox,Orcus,Exitus,Pestilentia");
//	n = AddStr2Array(&sRndShpPiName, n, "Black Heart,Blarney Cock");	// LDH if this line is being used, delete it - 04Jan09
	if(GetCurrentPeriod() >= PERIOD_COLONIAL_POWERS)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Queen Annes Revenge,Royal James");
	}
		
	// Holland names
	n = 0;
	n = AddStr2Array(&sRndShpHoName, n, "Bruynvisch,Eendracht,Neptunis,Gelderland,Hasewint,Tonijn,Zeeridder,Dolphijn,Groene Draeck,Haerlem,Postpaert,Jonas,Orangieboom,Wassende Maan,Amsterdam,Campel,Edam,Gecroonde Leeuw");
	n = AddStr2Array(&sRndShpHoName, n, "Gouda,Leiden,Meerman,Omlandia,Overijssel,Swarte Leeuw,Thetis,Vliegend Hert,Vriesland,Zeeland,Gouden Leeuw,Groene Draeck,Hollandsche Tuijn,Hoop,Medemblik,Prins Hendrik,Fredrik Hendrik");
	n = AddStr2Array(&sRndShpHoName, n, "Breda,Deventer,Drenthe,Gideon,Meerminne,Utrecht,Vlissingen,Walcheren,Wapen van Holland,Wapen van Nassau,Zierikzee,Bommel,Groot Christoffel,Omlandia,Sint Laurens,Wapen van Zeeland");
	n = AddStr2Array(&sRndShpHoName, n, "Nassau,Gekroonde Liefde,Eenhoorn,Jonge Prins,Hollandsche Tuin,West Capelle,Gorkum,Kasteel van Medemblik,Wapen van Monnikendam,Vergulde Zon,Ter Goes,Prinses Royaal,Vogelstruijs,Maan");
	n = AddStr2Array(&sRndShpHoName, n, "Zeven Provincien,Prinses Royaal Maria,Gouden Ster,Burcht van Alkmaar,Wapen van Enkhuijsen,Nijmegen,Faijsant,Prinses Louise,Westfriesland,Popkensburg,Akerboom,Noorderkwartier,Visschers Harder");
	n = AddStr2Array(&sRndShpHoName, n, "Beschermer,Carolus Quintus,Galei van Dover,Geldersche Ruiter,Moritz,Venus");

	// Portugal names
	n = 0;
	n = AddStr2Array(&sRndShpPoName, n, "Adamastor,Dom Carlos I,Douro,Santa de Concei��o,Pr�ncipe Real,Conde Dom Henrique,Maria I,Medusa,Princesa de Beira,Pr�ncipe Regente,Reinha do Portugal,S�o Ant�nio e S�o Jose,Vasco da Gama,Alfonso de Albuquerque,Dom Jo�o de Castro");		//some portuguese ship names spell-checked by KAM
	n = AddStr2Array(&sRndShpPoName, n, "Infante Dom Pedro,Santa de Belem,Santa de Bom Succeso,Martin de Freitas,S�o Sebasti�o,F�nix,Gra�a,Amazana,Minerva,Princesa Carlota,Perola,Pr�ncipe de Brazil,Trit�o,Bolfinho,Ulisses,Ur�nia,Cisne,Plongeur,Espadarte,Golfinho,Hidra");
	n = AddStr2Array(&sRndShpPoName, n, "Princesa de Brazil,Thetis,Torta,Venus,Josefa,S�o Ant�nio e �sia Feliz,Sao Gabriel,Sao Rafael,Benjamin,Princesa Real,San Jo�o Magn�nimo,Condessa de Resonde,S�o Ant�nio,�guia,Gl�ria,Neptuno,Pol�femo,Falc�o,Giavota,Lebre");
	n = AddStr2Array(&sRndShpPoName, n, "Sem Nome,Serpente de Mar,Voador,Galgo,Vingan�a,Amorale,Curiosa,Coroa,Princesa,Pr�ncipe,Isabel,Costanca,Laocadia,Tareia,Tina-Maria,Hel�nica,Marta-Alexandra,Dores,Aldonca,Josefa,Violante,Luciana,Alvares Cabral,Corte Real");
	n = AddStr2Array(&sRndShpPoName, n, "Betriz,Etelvina,Rainha Dona Amelia,Maria-Augusta,S�nia,Bella,Fernanda,Guiomar,Meiguinha,Teresa,Vasco Da Gama,D Francisco De Almeida,Almirante Magalhaes Correa,Commandante Joao Belo,Vasco Da Gama,Espardarte,Vulcano");
	n = AddStr2Array(&sRndShpPoName, n, "Tejo,Tamega,Vouga,Gaudiana,Diogo Cao,Corte Real,Nuno Tristao,Pedro Escobar,Almirante Gago Coutinho,Almirante Pereira Da Silva,Alvares Cabral,Commandante Roberto Ivens,Commandante Sacadura Cabral,Joao Coutinho");
	n = AddStr2Array(&sRndShpPoName, n, "Jacinto Candido,General Pereira D'Eca,Augusto De Castilho,Honorio Barreto,Antonio Enes,Baptiste De Andrada,Joao Roby,Alfonso Cerqueira,Oliveira E Carmo,Commandante Pedro Campbell");
	n = AddStr2Array(&sRndShpPoName, n, "O Tem�vel,O Temido,O Minho,O Timor,O Supremo,O Sonho,O Sonhador,O Solit�rio,O Perempt�rio,O Perfeito,O Pavor,O Ousado,O Not�vel,O Furac�o");
	n = AddStr2Array(&sRndShpPoName, n, "Santa Virgem,S�o Bartolomeu,S�o Miguel,S�o Jo�o de Arga,Santa Luzia,Santo Ant�nio,Senhora da Gra�a,Senhora da Vista,S�o Silvestre,S�o Mamede,S�o Bento,Boa Morte,Santo Amaro,S�o Br�s");
	n = AddStr2Array(&sRndShpPoName, n, "Senhora do Fastio,Senhora da Aparecida,Senhora do Faro,S�o Jo�o Baptista,Terra de Cerveira,Santo Aginha,Foz do Coura,Santa Marta,S�o Jo�o da Ribeira,Santa Maria,O Bom Jesus,Dom Sancho I,Melga�o Velho,O Santu�rio do Rei");
	n = AddStr2Array(&sRndShpPoName, n, "O Foz do Lima,Vinha da Rainha,Salvador do Monte,Santa Eul�lia,Santa Cruz,Santa Comba,Santa Catarina,Santa Clara,Santo Vit�ria,S�o Pedro,S�o Geraldo,Rio Tinto,Rio Maior,Rainha Santa Isabel");
	n = AddStr2Array(&sRndShpPoName, n, "Andorinha,Monte dos Corvos,Senhora das Neves,Santa Cristina,Pedras Negras,S�o Bernardino,Porto de M�s,Costa Nova,S�o Vicente,Ponte de Sagres,Monte da Piedade,Santa B�rbara,S�o Martinho");
	n = AddStr2Array(&sRndShpPoName, n, "Cavaleiro Preto,Ilha Terceira,Ilha da Madeira,Vila Azeda,S�o Rom�o,Monte Real,Boa Viagem,Martingan�a,Consola��o,Calvaria de Cima,Pinheiro Grande,Rio de Moinhos,Moita da Roda,Mata Mourisca");
	n = AddStr2Array(&sRndShpPoName, n, "Foz de Arouce,Alcaria Nova,Ninho do A�or,O Horrendo,Her�i do Mar,Penamacor,Terreiro das Bruxas,Vila de Santar�m,Alfama,S�o Roque,Torre de Bel�m,Madre de Deus,Jardim do Mar,Boca do Inferno");

	// American names
	n = 0;
	n = AddStr2Array(&sRndShpAmName, n, "Adams,Albany,Alfred,Alliance,Alligator,America,Andrew Doria,Annapolis,Argus,Baltimore,Bella Italia,Betsy Ross,Biddle,Bonhomme Richard,Boston,Bourbon,Bunker Hill,Brandywine,Brockenborough,Cabot,Caroline,Champlain,Charles W Morgan,Charlestowne,Charlotte,Chesapeake,Chippewa,Clara,Columbia,Columbus,Concord,Confederacy");
	n = AddStr2Array(&sRndShpAmName, n, "Congress,Connecticut,Constellation,Constitution,Cumberland,Cyane,Dale,Deane,Decatur,Deleware,Diana,Dolphin,Eagle,Effingham,Elizabeth,Endeavor,Enterprise,Epervier,Erie,Essex,Experiment,Fair American,Francine,Fairfield,Falmouth,Freedom,Frolic,Ganges,General Greene,Georgia,Germantown");
	n = AddStr2Array(&sRndShpAmName, n, "Granite,Growler,Guerriere,Hamilton,Hampton,Hancock,Helen,Hopkins,Hornet,Hudson,Hyder Aly,Independence,Insurgent,Jamestown,Java,Julia,Lady Washington,Lafayette,Levant,Lexington,Liberty,Macedonian,Madison,Marion,Mary Sears,Maryland,Massachusetts,Merrimack,Minuteman");
	n = AddStr2Array(&sRndShpAmName, n, "Mohawk,Molly,Montgomery,Montezuma,Nantucket,Natchez,New Hampshire,New Jersey,New York,Newport,Norfolk,North Carolina,Ohio,Ontario,Oriole,Patrick Henry,Patriot,Peacock,Pennsylvania,Philadelphia,Pilgrim,Plattburg,Plymouth,Pocahontas,Portsmouth,Potomac,Preble,President,Pride,Providence");
	n = AddStr2Array(&sRndShpAmName, n, "Quinnebaug,Raleigh,Ranger,Randolph,Raritan,Retaliation,Revolutionary,Rhode Island,Roger,Roxbury,Sabine Sacagawea,Santee,Sarapis,Saratoga,Savannah,Scourge,South Carolina,Sovereign,St Lawrence,St Louis,Superior,Surprise,Trenton,Trippe,Trumble,United States,Vermont,Venus,Virginia,Warren,Wasp,Yorktown");
	if(GetCurrentPeriod() == PERIOD_NAPOLEONIC)
	{
		n = AddStr2Array(&sRndShpEnName, n, "Franklin,Jefferson,John Adams,George Washington,Washington");
	}	
	// Swedish names
	n = 0;
	n = AddStr2Array(&sRndShpSwName, n, "�lgen,�lvsborg,�ngeln,�ngeln Gabriel,�pplet,�rtan,�len,�ngermanland,�rnen,�rnen,Abraham,Achilles,Amalia,Amarant,Amphion,Andromeda,Angelus,Anna,Apelbom,Apollo");
	n = AddStr2Array(&sRndShpSwName, n, "Arvid,B�nan,B�se Lejon,Baggen,Basiliscus,Bellona,Bj�rnen,Bl� Falk,Bl� Lejonet,Bl� M�ne,Bl� Mannen,Bl� Ormen,Blekinge,Blomman,Bohus,Brommaren,Bruna Lejon,Brune Bj�rnen,Buffeln,Caesar");
	n = AddStr2Array(&sRndShpSwName, n, "Carolus,Cronstierna,Danska Phoenix,Danziger Svanen,David,Delfinen,Draken,Dristigheten,Dromedarius,Drottningen,Duvan,Dygden,Ekorren,Elefanten,Enh�rningen,Enigheten,Estland,F�rgyllda �pplet,F�rgyllda Duvan,F�rgyllda Hjorten");
	n = AddStr2Array(&sRndShpSwName, n, "F�rgyllda Lejonet,F�rgyllda Rosen,F�rsiktigheten,Falken,Fenix,Finland,Finska Memnon,Flygande Drake,Flygande Vargen,Fortuna,Fr�ja,Fr�ken Eleonora,Fredrika Amalia,Friheten,G�ddan,G�ta Lejon,G�teborg,Gamla Sv�rdet,Gamle Frantsen,Gotland");
	n = AddStr2Array(&sRndShpSwName, n, "Gr� Ulven,Gr�ne J�garen,Greken,Greve Sparre,Gripen,Gule Lejonet,Gustavus,Gyllenstiernan,H�gern,H�ken,Halland,Halvm�nen,Hanen,Hannibal,Havh�sten,Havsfrun,Herdinnan,Herkules,Hjorten,Holken");
	n = AddStr2Array(&sRndShpSwName, n, "Hummern,Hunden,Hvita �rn,Igeln,Ilskan,J�garen,Jonas,Jungfrun,Jupiter,Justitia,K�mpen,Kalmar,Kattan,Korpen,Kr�ftan,Kr�kan,Krabaten,Krabban,Kristina,Lammet");
	n = AddStr2Array(&sRndShpSwName, n, "Laxen,Lejonet,Lejoninnan,Leoparden,Liljan,Lindormen,M�nen,M�sen,Makal�s,Makrillen,Manligheten,Maria,Mars,Mercurius,Mj�lkpigan,N�ktergalen,N�svis,Neptunus,Nordstjernan,Nyckeln");
	n = AddStr2Array(&sRndShpSwName, n, "Ormen,Oxen,Papegojan,Pelikanen,Phoenix,R�bocken,R�da Gripen,R�da Lejonet,R�de Lejonet,Recompens,Regina,Renen,Resande Man,Rosen,S�len,Sankt Erik,Sankt G�ran,Saturnus,Siken,Sj�katten");
	n = AddStr2Array(&sRndShpSwName, n, "Solen,St�ln�bben,Stenbock,Stj�rnan,Stockholm,Storken,Stormaren,Strutsen,Sundsvall,Sv�rdet,Sv�rdet,Svanen,Svarta Hunden,Svarte Rappen,Svarte Ryttaren,Sven,Tapperheten,Tigern,Tranan,Tre Kronor");
	n = AddStr2Array(&sRndShpSwName, n, "Tre Lejon,Tumlaren,Ugglan,Ulven,Unge Ryttaren,Upland,Uttern,V�lkomsten,Valen,Vargen,Venus,Viktoria");
}
