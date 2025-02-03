# Change to src directory
cd src

# Exceutes the Makefile
make -f Makefile
# Check to see if make was successful
if [ $? -ne 0 ]; then
  echo "Error: make command failed."
  exit 1
fi

# Go back to the gcal directory
cd ..  
echo "Compiled gcal"

# Set the installation directory
INSTALL_DIR="$HOME/.local/bin"
echo "Directory $INSTALL_DIR already exists"

# Create the installation directory if it doesn't exist
mkdir -p "$INSTALL_DIR" # Create the directory
# Check if directory creation was successful
if [ $? -ne 0 ]; then 
  echo "Error: Could not create directory: $INSTALL_DIR"
  exit 1
fi

# Copy the executable file to the installation directory
echo "Installed gcal to $INSTALL_DIR"
cp src/gcal "$INSTALL_DIR"
if [ $? -ne 0 ]; then
  echo "Error: Could not copy gcal executable."
  exit 1
fi

# Check if the PATH is already added
if grep -q "export PATH=\"$INSTALL_DIR:\$PATH\"" ~/.bashrc; then
    echo "$INSTALL_DIR is already in PATH." # Inform user if the path is already added
else
  # Add the installation directory to PATH
  echo "export PATH=\"$INSTALL_DIR:\$PATH\"" >> ~/.bashrc
  if [ $? -ne 0 ]; then
      echo "Error: Could not update ~/.bashrc"
      exit 1
  fi
fi

echo "Installation complete."