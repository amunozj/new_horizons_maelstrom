import argparse
import sys
import numpy as np


TRACK1_ZSTART_OFFSET = -0.1
TRACK1_SPEED_FACTOR = 10.1


TRACK2_ZSTART_OFFSET = -0.1
TRACK2_SPEED_FACTOR = 10.0


parser = argparse.ArgumentParser()
parser.add_argument(
    '--nh_dir',
    type=str,
    default=None,
    required=True,
    help='Location of raw ship file'
)

parser.add_argument(
    '--output_dir',
    type=str,
    default="",
    required=True,
    help='Output folder'
)


def ships_add_wake(
    nh_dir=None,
    output_dir=None
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

    initShipsOutputFile = output_dir + 'Ships_init.c'
    initShipsOutputFile = open(initShipsOutputFile, 'w')

    new_model_definition = False
    ship_has_wake = False
    for index, line in enumerate(initModelslines):

        initShipsOutputFile.write(line)

        if index>144 and index<18383:        

            # Find beginning of ship model definition
            if not new_model_definition:

                if 'n++' in line:
                    new_model_definition = True
                    ship_has_wake = False
                    weight = None
                    sclass = None
                    capacity = None

            else:

                if 'refShip.' in line:
                    shipProperty = line.split('refShip.')[1].split('=')[0].replace(' ', '').replace('\t', '')
                    shipValue = line.split('=')[1].replace('"','').replace(' ', '').replace('\t', '').replace('\n', '').replace(';', '').split('//')[0]

                    if shipProperty.lower() == 'weight':
                        weight = np.array(shipValue.split('(')[1].split(')')[0]).astype('float')

                    if shipProperty.lower() == 'class':
                        sclass = np.array(shipValue).astype('float')

                    if shipProperty.lower() == 'capacity':
                        capacity = np.array(shipValue).astype('float')

                if not ship_has_wake and weight is not None and sclass is not None and capacity is not None and len(line) < 4:

                    initShipsOutputFile.write('\trefShip.Track.Enable = true;\n')

                    coeff = [1.55517214e-02, 5.00225823e-05, -4.98928074e-06]
                    intercept = 0.09820077736886756
                    value = -0.2 # sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept + TRACK1_ZSTART_OFFSET
                    initShipsOutputFile.write(f'\trefShip.Track1.ZStart = {np.round(value, 2)};\n')

                    coeff = [-0.62688704, -0.00091369, 0.00088025]
                    intercept = 13.210084408616721
                    value = 20.0# sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    initShipsOutputFile.write(f'\trefShip.Track1.LifeTime = {int(np.round(value, 1))};\n')

                    coeff = [-0.08050374, 0.00034216, 0.00045451]
                    intercept = 2.223110932622534
                    value1 = 1.0# sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    coeff = [0.10751939, 0.00012831, 0.00070964]
                    intercept = 1.7119858376185348
                    value2 = 2.0#sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    initShipsOutputFile.write(f'\trefShip.Track1.Width = "{np.round(value1, 1)}, {np.round(value2, 1)}";\n')

                    coeff = [0.0228987, 0.00079388, -0.00019649]
                    intercept = 6.630231071240672
                    value1 = 0.1#(sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept)*TRACK1_SPEED_FACTOR
                    coeff = [0.02616642, 0.00055361, -0.00022146]
                    intercept = 8.315454087729835
                    value2 = 0.15#(sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept)*TRACK1_SPEED_FACTOR
                    initShipsOutputFile.write(f'\trefShip.Track1.Speed = "{np.round(value1, 1)}, {np.round(value2, 1)}";\n\n')

                    coeff = [4.67918432e-03, 2.00266650e-05, -5.72896726e-06]
                    intercept = -0.16740627232249805
                    value = -0.25#sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept + TRACK2_ZSTART_OFFSET
                    initShipsOutputFile.write(f'\trefShip.Track2.ZStart = {np.round(value, 2)};\n')                
                    # initShipsOutputFile.write(f'\trefShip.Track2.ZStart = {-0.15};\n')                

                    coeff = [0.01688486, 0.00057339, 0.00019802]
                    intercept = 6.662296537342268
                    value = 20.0#sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    initShipsOutputFile.write(f'\trefShip.Track2.LifeTime = {int(np.round(value, 1))};\n')

                    coeff = [-0.19453281, 0.00101803, 0.0006664]
                    intercept = 3.8901838205823576
                    value1 = 5.2#sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    coeff = [-0.1736205, 0.00074637, 0.00084421]
                    intercept = 5.042083500051052
                    value2 = 7.0#sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept
                    initShipsOutputFile.write(f'\trefShip.Track2.Width = "{np.round(value1, 1)}, {np.round(value2, 1)}";\n')

                    coeff = [-4.28609993e-03, 1.20394955e-04, -2.04583143e-05]
                    intercept = 0.1745199323568355
                    value1 = -5.05#(sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept)*TRACK2_SPEED_FACTOR
                    coeff = [-8.82432338e-03,  2.47871965e-04, -4.21200588e-05]
                    intercept = 0.30048221367583794
                    value2 = -1.15#(sclass*coeff[0] + weight*coeff[1] + capacity*coeff[2] + intercept)*TRACK2_SPEED_FACTOR
                    initShipsOutputFile.write(f'\trefShip.Track2.Speed = "{np.round(value1, 2)}, {np.round(value2, 2)}";\n\n')

                    ship_has_wake = True
                    new_model_definition = False

    initShipsFile.close()
    initShipsOutputFile.close()


if __name__ == "__main__":

    print(sys.argv)

    print(parser.parse_known_args(sys.argv))
    args = vars(parser.parse_known_args(sys.argv)[0])
    print(args)

    ships_add_wake(**args)