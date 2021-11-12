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

class ship_model:
    """
    Model class to store a dictionary with all the necessary parameters as well
        as flags to indicate gender and processing status
    """

    def __init__(self, model_list,
                nh_dir=None):
        """
        Initialization function of the storm_model class

        Parameters
        ----------
        model_list: list
            list with all entries read from initModel.c
        nh_dir: str
            Location of the New Horizons mod
        output_dir: str
            Folder for converted output                   
        """

        self.nh_dir = nh_dir
        self.output_dir = output_dir

        # create list with animation as comment
        self.comments_and_ending = ['//'+line for line in model_list if '.ani' in line and '//' not in line]
        #add all comments and ending
        self.comments_and_ending += [line for line in model_list if 'model.' not in line or '//' in line.split('model.')[0] or 'AssignModel' in line or 'IF' in line]

        self.only_parameters = [line for line in model_list if 'model.' in line and '//' not in line.split('model.')[0] and 'AssignModel' not in line and '.ani' not in line]
        self.model_parameters = {}

        # Fill parameter dictionary
        for line in self.only_parameters:
            parameter = line.split('model.')[1].split('=')[0].replace(' ', '').replace('\t', '')
            self.model_parameters[parameter] = line.split('=')[1].replace('\t', '').strip()
        
        # Make sure the model has an assigned sex
        if 'sex' not in self.model_parameters:
            self.model_parameters['sex'] = '"man";'

        # Store flag to indicate that the model has an animation different than "man" or "woman_sit"
        self.standard_ani = True
        if 'ani' in self.model_parameters:
            if self.model_parameters['ani'] == '"woman_sit";' or self.model_parameters['ani'] == '"man";':
                self.standard_ani = True
            else:
                self.standard_ani = False

        # Assemble model file name
        self.model = self.model_parameters['id'].split('"')[1]
        self.model_file = self.model + ".gm"

        # clean sex string, set animation files, and conversion flags
        self.convert_potc_to_coas_man=False
        self.convert_potc_to_coas_woman=False
        if 'woman' in self.model_parameters['sex']:
            self.sex = 'woman'
            self.an_path = self.output_dir + f'/RESOURCE/animation/woman_coas.an'
            self.convert_potc_to_coas_woman = True
            self.model_parameters['ani'] = '"woman_coas";'
            
        elif 'monkey' in self.model_parameters['sex']:
            self.sex = 'monkey'

        elif 'skeleton' in self.model_parameters['sex']:
            self.sex = 'skeleton'
            self.an_path = self.output_dir + f'/RESOURCE/animation/man_coas.an'
            self.convert_potc_to_coas_man = True
            self.model_parameters['ani'] = f'"man";'
        else:
            self.sex = 'man'
            self.an_path = self.output_dir + f'/RESOURCE/animation/man_coas.an'
            self.convert_potc_to_coas_man = True

        # Define parameters for import
        self.filepath = self.nh_dir + f'/RESOURCE/MODELS/Characters/{self.model_file}'
        self.textures_path = self.nh_dir + '/RESOURCE/Textures/Characters/'
        
        self.fix_coas_man_head = False
        self.convert_coas_to_potc_man = False
        self.convert_coas_to_potc_woman = False

        # Define parameters for export
        self.filepath_out = self.output_dir + f'/RESOURCE/MODELS/Characters/{self.model_file}'


    def print_to_file(self, initShipsOutputFile):
        """
        Function to print model into file

        Parameters
        ----------
        initShipsOutputFile: file
            file where to print the lines of each model       
        """

        for key, value in self.model_parameters.items():
            initShipsOutputFile.write(f'\tmodel.{key} = {value}\n')

        for line in self.comments_and_ending:
            initShipsOutputFile.write(line)


def ships_add_wake(
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
    
 

if __name__ == "__main__":

    print(sys.argv)

    print(parser.parse_known_args(sys.argv))
    args = vars(parser.parse_known_args(sys.argv)[0])
    print(args)

    ships_add_wake(**args)