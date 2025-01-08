#!/bin/bash

# Check if nvm is installed, and install it if not
if [ -z "$(command -v nvm)" ]; then
  echo "nvm is not installed. Installing nvm..."
  curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.3/install.sh | bash
  export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
  [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"
else
  echo "nvm is already installed."
fi

# Install the latest version of Node.js
nvm install node

# Verify the installation
node -v
npm -v

echo "Node.js and npm have been installed successfully."
