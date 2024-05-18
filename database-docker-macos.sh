brew install docker

open --background -a Docker

while ! docker system info > /dev/null 2>&1; do
  echo "Waiting for Docker to start..."
  sleep 1
done

docker pull existq/main:reminder

docker run -d -p 5432:5432 --name reminder-database existq/main:reminder

