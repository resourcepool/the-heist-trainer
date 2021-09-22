FROM node:12 AS the-heist-server

ARG NODE_ENV=production
ENV NODE_ENV=${NODE_ENV}
WORKDIR /server

RUN apt-get update && apt-get install libpcsclite1 libpcsclite-dev

COPY ./server/package*.json ./

RUN npm install

COPY ./server .

RUN npm run build

COPY /server/dist ./dist

CMD ["node", "dist/main"]

FROM node:12-alpine AS the-heist-website

WORKDIR /website

COPY ./website/package*.json ./

RUN npm install

COPY ./server/src/_interface ../server/src/_interface
COPY ./website .

RUN npm run build

COPY /website/dist ./dist
