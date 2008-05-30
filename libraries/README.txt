these are the external libraries that entonetics uses.
There will be customization for each as the project develops
The libraries themselves will also update.

To avoid the headache of remerging customization into each new revision of the library, we will maintain our own copy.

The copies in this directory should be untouched from the original repo.
The project customization will be done on the branches located in the trunk.

The head of each library has two properties set.
original_url
current_rev

There is also a script to update these copies from their original repos it is called update.py see the script for more details
