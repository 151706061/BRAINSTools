# -*- coding: utf8 -*-
"""Autogenerated file - DO NOT EDIT
If you spot a bug, please report it on the mailing list and/or change the generator."""

from nipype.interfaces.base import CommandLine, CommandLineInputSpec, SEMLikeCommandLine, TraitedSpec, File, Directory, traits, isdefined, InputMultiPath, OutputMultiPath
import os


class BRAINSContinuousClassInputSpec(CommandLineInputSpec):
    inputT1Volume = File(desc="Required: input T1 image", exists=True, argstr="--inputT1Volume %s")
    inputT2Volume = File(desc="Required: input T2 image", exists=True, argstr="--inputT2Volume %s")
    inputDiscreteVolume = File(desc="Required: input discrete image", exists=True, argstr="--inputDiscreteVolume %s")
    outputVolume = traits.Either(traits.Bool, File(), hash_files=False, desc="Required: output continuous classified image", argstr="--outputVolume %s")


class BRAINSContinuousClassOutputSpec(TraitedSpec):
    outputVolume = File(desc="Required: output continuous classified image", exists=True)


class BRAINSContinuousClass(SEMLikeCommandLine):

    """title:  Predict Lesions

category: Segmentation.ContClassImage

description: Creates a continuous classified image.

version: 0.1.0.$Revision: 1.3 $(alpha)

documentation-url: http:://www.na-mic.org/

license: NEED TO ADD

contributor: This tool was developed by Mark Scully.

"""

    input_spec = BRAINSContinuousClassInputSpec
    output_spec = BRAINSContinuousClassOutputSpec
    _cmd = " BRAINSContinuousClass "
    _outputs_filenames = {'outputVolume': 'outputVolume.nii'}