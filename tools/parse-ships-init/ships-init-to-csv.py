import argparse
import os
import sys
import numpy as np
import pandas as pd


parser = argparse.ArgumentParser()
parser.add_argument(
    '--nh_dir',
    type=str,
    default=None,
    required=True,
    help='Location of the New Horizons mod'
)

def ships_make_csv(
    nh_dir=None
    ):
    """Batch process initModels.c

    Parameters
    ----------
    nh_dir: str
        Location of the New Horizons mod
    output_dir: str
        Folder for converted output
    """

    initShipsFile = nh_dir + '/PROGRAM/Ships/Ships_init.c'
    initShipsFile = open(initShipsFile, 'r')
    initModelslines = initShipsFile.readlines()

    column_names = ['Name', 'Class', 'Weight', 'Capacity', 'CannonsQuantity', 'Track1.ZStart', 'Track1.LifeTime', 'Track1.Width', 'Track1.Speed', 'Track2.ZStart', 'Track2.LifeTime', 'Track2.Width', 'Track2.Speed']
    shipsdDf = pd.DataFrame(columns = column_names)

    ship_n = -1
    for index, line in enumerate(initModelslines):

        if index>144 and index<18383:

            if 'makeref(refShip,ShipsTypes' in line:
                ship_n += 1

            # If the line has a model definition
            if 'refShip.' in line:
                shipProperty = line.split('refShip.')[1].split('=')[0].replace(' ', '').replace('\t', '')
                shipValue = line.split('=')[1].replace('"','').replace(' ', '').replace('\t', '').replace('\n', '').replace(';', '')

                if shipProperty == 'Weight':
                    shipValue = shipValue.split('(')[1].split(')')[0]
                
                if shipProperty in column_names:
                    if ',' in shipValue:
                        shipValue = np.array(shipValue.split(',')).astype('float')

                    shipsdDf.loc[ship_n, shipProperty] = shipValue

 
    initShipsFile.close()
    shipsdDf.to_csv('ship_init.csv')

 

if __name__ == "__main__":

    print(sys.argv)

    print(parser.parse_known_args(sys.argv))
    args = vars(parser.parse_known_args(sys.argv)[0])
    print(args)

    ships_make_csv(**args)