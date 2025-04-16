# Create Local Docker Registry
docker run -d -p 50000:5000 --name chicken-jockey registry:2
# Build Docker Image
docker build -t reisenx.localhost:50000/app ./program
# Push Docker image to the registry
docker push reisenx.localhost:50000/app
# Run Docker image
docker run -e secret_user=Krerk reisenx.localhost:50000/app