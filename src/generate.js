const building0 = {
  ground_polygon: [[0, 0], [5, -2], [10, 0], [10, 10], [0, 10]],
  height: 10
};

const building1 = {
  ground_polygon: [[0, 20], [10, 20], [10, 30], [0, 30]],
  height: 10
};

const building2 = {
  ground_polygon: [[0, 40], [10, 40], [10, 50], [0, 50]],
  height: 10
};

const buildings = [building0, building1, building2];

export function generate() {
  return {
    buildings: new Float32Array(
      buildings.flatMap(building => {
        const { ground_polygon, height } = building;
        const flatBuilding = [];

        flatBuilding.push(ground_polygon.length * 2);

        for (let i = 0; i < ground_polygon.length; i++) {
          flatBuilding.push(ground_polygon[i][0]);
          flatBuilding.push(ground_polygon[i][1]);
        }
        flatBuilding.push(height);

        return flatBuilding;
      })
    ),

    setBuildings(buildings) {
      this.buildings = buildings;

      (this.listeners || []).forEach(listener => listener(this.buildings));
    },

    getBuildings() {
      return this.buildings;
    },

    onChange(listener) {
      this.listeners = this.listeners || [];
      this.listeners.push(listener);
    }
  };
}
